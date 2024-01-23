/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabourd <mrabourd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 15:04:54 by mrabourd          #+#    #+#             */
/*   Updated: 2024/01/23 15:31:08 by mrabourd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server() {

}

Server::Server(char *port, char *passwd) {
	if (this->setPort(port) == false)
		std::cerr << "The port is not valid!" << std::endl;
	if (this->setPasswd(passwd) == false)
		std::cerr << "The password is not valid!" << std::endl;
}

Server::~Server() {

}

bool	Server::setPort (char *port){
	this->_str_port = port;
	this->_port = atoi(port);
	if (this->_port >= 6665 && this->_port <= 6697)
		return (true);
	return (false);
}

bool	Server::setPasswd (char *passwd){
	this->_str_passwd = passwd;
	if (strlen(passwd) <= 0)
		return (false);
	this->_passwd = passwd;
	return (true);

}

/*int getaddrinfo(const char *restrict node,
                       const char *restrict service,
                       const struct addrinfo *restrict hints,
                       struct addrinfo **restrict res);
'node' = host;
'service' = port;

returns one or more addrinfo structures.
					   */

void Server::init () {

	this->_hints.ai_family = AF_UNSPEC;
	this->_hints.ai_socktype = SOCK_STREAM;
	this->_hints.ai_flags = AI_PASSIVE;
	/*if AI_PASSIVE and 'node' is NULL: the returned socket addresses will be suitable for
       binding a socket that will accept connections.*/
	this->_hints.ai_protocol = IPPROTO_TCP;
	this->_hints.ai_canonname = NULL;
    this->_hints.ai_addr = NULL;
    this->_hints.ai_next = NULL;

	struct addrinfo *res, *rp;
	int getaddr = getaddrinfo(NULL, _str_port, &_hints, &res);
    if (getaddr != 0) {
		std::cerr << "Error while getaddrinfo!" << std::endl;
        // fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(getaddr));
        exit(EXIT_FAILURE);
    }

    /* getaddrinfo() returns a list of address structures.
       Try each address until we successfully bind(2).
       If socket() (or bind()) fails, we (close the socket
       and) try the next address. */

	/* in 'res', we have a pointer to the first item in a linked list of 
	possible addresses that we can connect to. Each item in the list 
	has the associated kinds of family, socket type, and protocol. 
	We want to find one that we can connect to, so we loop through them: */

    for (rp = res; rp != NULL; rp = rp->ai_next) {
		this->_server_fd = socket(rp->ai_family, rp->ai_socktype,
				rp->ai_protocol);
		if (this->_server_fd == -1)
			continue;

		if (bind(this->_server_fd, rp->ai_addr, rp->ai_addrlen) == 0)
			break; /* = Success */

		close(this->_server_fd);
    }

	if (rp == NULL) {               /* No address succeeded */
        std::cerr << "Error while binding!" << std::endl;
		// fprintf(stderr, "Could not bind\n");
        exit(EXIT_FAILURE);
	}

	if (listen(this->_server_fd, SOMAXCONN) == -1){
		std::cerr << "Server is not listening!" << std::endl;
		exit(EXIT_FAILURE);
	}

	std::cout << "Server is well initiated!!!!!!! " << std::endl;
}

void	Server::createEpoll(){
	int epollFd;
	struct epoll_event event;
	struct epoll_event events[MAX_EVENTS];

	/* create epoll instance */
	epollFd = epoll_create1(0);
	if (epollFd == -1) {
		// perror ("epoll_create");
		std::cerr << "Failed to create epoll instance" << std::endl;
		close(this->_server_fd);
		exit(EXIT_FAILURE);
	}

	/* add server socket to epoll */
	event.events = EPOLLIN;
	event.data.fd = this->_server_fd;
	if (epoll_ctl(epollFd, EPOLL_CTL_ADD,
		this->_server_fd, &event) == -1){
		// perror ("epoll_ctl");
		std::cerr << "Failed to add server socket to epoll instance" << std::endl;
		close (this->_server_fd);
		close (epollFd);
		exit (EXIT_FAILURE);
	}
	std::cout << "Server started. Listening on port " << this->_port << std::endl;

	while (true) {
		int numEvents = epoll_wait(epollFd, events, MAX_EVENTS, -1);
		if (numEvents == -1){
			// perror("epoll_wait");
			std::cerr << "Failed to wait for events" << std::endl;
			break;
		}
		// std::cout << "num event: " << numEvents << std::endl;
		for (int i = 0; i < numEvents; ++i) {
			int fd = events[i].data.fd;
			if (fd == this->_server_fd){
				/* accept new client connection */
				std::cout << "Client " << i << " says: hey!" << std::endl;
				struct sockaddr_in clientAddress;
				socklen_t clientAddressLenght = sizeof(clientAddress);
				int clientFd = accept(this->_server_fd,
					(struct sockaddr *)&clientAddress, &clientAddressLenght);
				if (clientFd == -1){
					std::cerr << "Failed to accept client connection" << std::endl;
					close (this->_server_fd);
					exit(EXIT_FAILURE);
				}
				
				/* Make the new connection non blocking */
				fcntl(clientFd, F_SETFL, O_NONBLOCK);
				
				/* Add client socket to epoll */
				event.events = EPOLLIN;
				event.data.fd = clientFd;
				if (epoll_ctl(epollFd, EPOLL_CTL_ADD, clientFd, &event) == -1){
					std::cerr << "Failed to add client socket to epoll instance" << std::endl;
					close (clientFd);
					continue;
				}
			}
			else if ((events[i].events & EPOLLERR)  ||
						(events[i].events & EPOLLHUP) ||
						(!(events[i].events & EPOLLIN))) {
				std::cout << "Client connection closed" << std::endl;
				close(fd);
			}
			else {
				recv_and_forward_msg(fd);
				// int clientFd = events[i].data.fd;
				// char buffer[10];
				// // recv(fd, buffer, sizeof(buffer), 0);
				// int bytes = read(clientFd, buffer, sizeof(buffer));
				// // buffer[sizeof(buffer)] = 0;
				// std::cout << bytes << std::endl;
				// std::cout << "server's output: " << buffer << std::endl;
				// // send(this->_server_fd, buffer, sizeof(buffer), 0);
				// write(this->_server_fd, buffer, bytes);
				// while (bytes == read(this->_server_fd, buffer, sizeof(buffer))){
				// 	write(clientFd, buffer, bytes);
				// }
				// close(fd);
			}
		}
	}
}

void Server::recv_and_forward_msg(int fd){
	std::string remainder = "";
	while (1){
		char buffer[10];
		int ret_data = recv(fd, buffer, sizeof(buffer), 0);
		if (ret_data > 0){
			std::string msg(buffer, buffer + ret_data);
			msg = remainder + msg;
			
			std::vector<std::string> parts = split(msg, "<EOM>");
			remainder = msg;

			// forward_msg(parts);
			std::cout << "Apres split: " << msg << std::endl;
		}
		else
			break;
	}
}

std::vector<std::string > Server::split(std::string &s, std::string del){
	size_t pos = 0;
	std::vector < std::string > parts;

	while ((pos = s.find(del)) != std::string::npos){
		std::string token = s.substr(0, pos);
		if (token.size() > 0)
			parts.push_back(token);
		s.erase(0, pos + del.length());
	}
	return (parts);
}

ssize_t Server::Send(const char *data, unsigned int len){
	return send(this->_server_fd, data, len, 0);
}

int Server::Receive(char *buffer, unsigned int len){
	return recv(this->_server_fd, buffer, len, 0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 15:04:54 by mrabourd          #+#    #+#             */
/*   Updated: 2024/01/23 15:26:14 by avedrenn         ###   ########.fr       */
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

    for (rp = res; rp != NULL; rp = rp->ai_next) {
		this->_socket_fd = socket(rp->ai_family, rp->ai_socktype,
				rp->ai_protocol);
		if (this->_socket_fd == -1)
			continue;

		if (bind(this->_socket_fd, rp->ai_addr, rp->ai_addrlen) == 0)
			break;                  /* Success */

		close(this->_socket_fd);
    }

	if (rp == NULL) {               /* No address succeeded */
        std::cerr << "Error while binding!" << std::endl;
		// fprintf(stderr, "Could not bind\n");
        exit(EXIT_FAILURE);
	}
	std::cout << rp->ai_addr << " is the address. " << std::endl;
	std::cout << this->_socket_fd << " is the socket fd. " << std::endl;

	if (listen(this->_socket_fd, SOMAXCONN) == -1){
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
		std::cerr << "Failed to create epoll instance" << std::endl;
		close(this->_socket_fd);
		exit(EXIT_FAILURE);
	}

	/* add server socket to epoll */
	event.events = EPOLLIN;
	event.data.fd = this->_socket_fd;
	if (epoll_ctl(epollFd, EPOLL_CTL_ADD,
		this->_socket_fd, &event) == -1){
		std::cerr << "Failed to add server socket to epoll instance" << std::endl;
		close (this->_socket_fd);
		close (epollFd);
		exit (EXIT_FAILURE);
	}
	std::cout << "Server started. Listening on port " << this->_port << std::endl;

	while (true) {
		int numEvents = epoll_wait(epollFd, events, MAX_EVENTS, -1);
		if (numEvents == -1){
			std::cerr << "Failed to wait for events" << std::endl;
			break;
		}
		std::cout << "num event: " << numEvents << std::endl;
		for (int i = 0; i < numEvents; ++i) {
			if (events[i].data.fd == this->_socket_fd){
				/* accept new client connection */
				std::cout << "server says: hey!" << std::endl;
				struct sockaddr_in clientAddress;
				socklen_t clientAddressLenght = sizeof(clientAddress);
				int clientFd = accept(this->_socket_fd,
					(struct sockaddr *)&clientAddress, &clientAddressLenght);
				if (clientFd == -1){
					std::cerr << "Failed to accept client connection" << std::endl;
					continue;
				}

				/* Add client socket to epoll */
				event.events = EPOLLIN;
				event.data.fd = clientFd;
				if (epoll_ctl(epollFd, EPOLL_CTL_ADD, clientFd, &event) == -1){
					std::cerr << "Failed to add client socket to epoll instance" << std::endl;
					close (clientFd);
					continue;
				}
			} else {
				char buffer[5];
				int clientFd = event.data.fd;
				read(clientFd, buffer, sizeof(buffer));
				buffer[sizeof(buffer)] = 0;
				std::cout << buffer << std::endl;
				write(clientFd, "shutup", 8);
			}
		}
	}
}


ssize_t Server::Send(const char *data, unsigned int len){
	return send(this->_socket_fd, data, len, 0);
}

int Server::Receive(char *buffer, unsigned int len){
	return recv(this->_socket_fd, buffer, len, 0);
}
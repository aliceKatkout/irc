/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabourd <mrabourd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 15:04:54 by mrabourd          #+#    #+#             */
/*   Updated: 2024/01/23 19:23:01 by mrabourd         ###   ########.fr       */
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

// void Server::init () {

// 	this->_hints.ai_family = AF_UNSPEC;
// 	this->_hints.ai_socktype = SOCK_STREAM;
// 	this->_hints.ai_flags = AI_PASSIVE;
// 	/*if AI_PASSIVE and 'node' is NULL: the returned socket addresses will be suitable for
//        binding a socket that will accept connections.*/
// 	this->_hints.ai_protocol = IPPROTO_TCP;
// 	this->_hints.ai_canonname = NULL;
//     this->_hints.ai_addr = NULL;
//     this->_hints.ai_next = NULL;

// 	struct addrinfo *res, *rp;
// 	int getaddr = getaddrinfo(NULL, _str_port, &_hints, &res);
//     if (getaddr != 0) {
// 		std::cerr << "Error while getaddrinfo!" << std::endl;
//         // fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(getaddr));
//         exit(EXIT_FAILURE);
//     }

//     for (rp = res; rp != NULL; rp = rp->ai_next) {
// 		this->_server_fd = socket(rp->ai_family, rp->ai_socktype,
// 				rp->ai_protocol);
// 		if (this->_server_fd == -1)
// 			continue;

// 		if (bind(this->_server_fd, rp->ai_addr, rp->ai_addrlen) == 0)
// 			break; /* = Success */

// 		close(this->_server_fd);
//     }

// 	if (rp == NULL) {               /* No address succeeded */
//         std::cerr << "Error while binding!" << std::endl;
// 		// fprintf(stderr, "Could not bind\n");
//         exit(EXIT_FAILURE);
// 	}

// 	if (listen(this->_server_fd, SOMAXCONN) == -1){
// 		std::cerr << "Server is not listening!" << std::endl;
// 		exit(EXIT_FAILURE);
// 	}

// 	std::cout << "Server is well initiated!!!!!!! " << std::endl;
// }

void Server::init()
{
	this->opt = 1;
	
	this->_server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (this->_server_fd < 0)
		exit(EXIT_FAILURE);
	
	if (setsockopt(this->_server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &this->opt, sizeof(this->opt)) < 0)
		exit (EXIT_FAILURE);
	
	this->serv_addr = sockaddr_in();
	this->serv_addr.sin_family = AF_INET;
	this->serv_addr.sin_port = htons(this->_port);			// specify port to listen on
	this->serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);	// bind to any local address
	/* htons(), htonl(): host to network short/long */

	if (bind(this->_server_fd, (struct sockaddr *)&this->serv_addr, sizeof(this->serv_addr)) < 0)
		exit(EXIT_FAILURE);

	this->size = sizeof(this->serv_addr);
	
	if (listen(this->_server_fd, MAX_EVENTS) < 0)
		exit(EXIT_FAILURE);
	
	std::cout << "YES SERVER DONE" << std::endl;
		
}

int Server::find_user_fd(int fd)
{
	std::map<int, User*>::iterator it = this->connectedUsers.begin();
	std::map<int, User*>::iterator ite = this->connectedUsers.end();

	for (; it != ite; ++it)
	{
		if (it->first == fd){
			return (it->first);
		}
		
	}
	return (-1); // a reverifier
}

void	Server::createEpoll(){
	int epollFd;
	struct epoll_event event = epoll_event();
	struct epoll_event events[MAX_EVENTS];

	std::cout << "server fd: " << this->_server_fd << std::endl;

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
		std::cout << "events->data.fd: " << events->data.fd << std::endl;
		
		if (numEvents == -1){
			// perror("epoll_wait");
			std::cerr << "Failed to wait for events" << std::endl;
			break;
		}
		// std::cout << "num event: " << numEvents << std::endl;
		for (int i = 0; i < numEvents; ++i) {
			// int fd = events[i].data.fd;
			const int fd = find_user_fd(events[i].data.fd);
			
			if (events[i].data.fd == this->_server_fd){
				/* accept new client connection */
				std::cout << "i: " << i << " says: hey!" << std::endl;
				
				struct sockaddr_in clientAddress;
				socklen_t clientAddressLenght = sizeof(clientAddress);
				
				int clientFd = accept(this->_server_fd,
					(struct sockaddr *)&clientAddress, &clientAddressLenght);
					
				User *newUser = new User(clientFd); // create user;
				newUser->getFd();
				this->connectedUsers.insert(std::pair<int, User *>(clientFd, newUser));
				
				if (clientFd == -1){
					std::cerr << "Failed to accept client connection" << std::endl;
					close (this->_server_fd);
					exit(EXIT_FAILURE);
				}
				
				/* Make the new connection non blocking */
				// fcntl(clientFd, F_SETFL, O_NONBLOCK);
				
				/* Add client socket to epoll */
				event.events = EPOLLIN | EPOLLRDHUP;
				event.data.fd = clientFd;
				if (epoll_ctl(epollFd, EPOLL_CTL_ADD, clientFd, &event) == -1){
					std::cerr << "Failed to add client socket to epoll instance" << std::endl;
					close (clientFd);
					continue;
				}
			}
			// else if ((events[i].events & EPOLLERR)  ||
			// 			(events[i].events & EPOLLHUP) ||
			// 			(!(events[i].events & EPOLLIN))) {
			// 	std::cout << "Client connection closed" << std::endl;
			// 	close(fd);
			// }
			else if (fd != -1) {
				std::cout << "events[i].data.fd: " <<  events[i].data.fd <<std::endl;
				recv_and_forward_msg(events[i].data.fd);
				close(events[i].data.fd);
			}
		}
	}
}



void Server::recv_and_forward_msg(int fd){
				
				/* A REVOIR */
				
	std::string remainder = "";
	std::vector<std::string> parts;
	while (1){
		char buffer[10];
		int ret_data = recv(fd, buffer, 10, 0);
		if (ret_data > 0){
			std::string msg(buffer, buffer + ret_data);
			msg = remainder + msg;
			
			parts = split(msg, "\n");
			remainder = msg;

			// forward_msg(parts);
			if (parts.empty() == true)
				std::cout << "\'parts\' is empty" << std::endl;
			else
				std::cout << parts.back() << std::endl;
			// std::cout << remainder << std::endl;
		}
		else{
			std::cout << "client breaks;" << std::endl;
			break;
		}
	}
}

std::vector<std::string > Server::split(std::string &s, std::string del){
	size_t pos = 0;
	std::vector < std::string > parts;

	while ((pos = s.find(del)) != std::string::npos){
		std::string token = s.substr(0, pos);
		if (token.size() > 0){
			parts.push_back(token);
		}
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
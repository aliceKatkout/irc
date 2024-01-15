/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabourd <mrabourd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 15:04:54 by mrabourd          #+#    #+#             */
/*   Updated: 2024/01/15 16:20:37 by mrabourd         ###   ########.fr       */
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

void Server::init () {
	
	this->_hints.ai_family = AF_UNSPEC;
	this->_hints.ai_socktype = SOCK_STREAM;
	this->_hints.ai_flags = AI_PASSIVE;
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
	std::cout << "Server is good!!!!!!! " << std::endl;
}

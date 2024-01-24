/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabourd <mrabourd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 15:04:54 by mrabourd          #+#    #+#             */
/*   Updated: 2024/01/24 14:09:20 by mrabourd         ###   ########.fr       */
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

void Server::start(){
	struct pollfd server_fd = {this->_server_fd, POLLIN, 0};
	this->_pollfds.push_back(server_fd);

	while (1){
		if (poll(_pollfds.begin().base(), _pollfds.size(), -1) < 0) {
			exit(EXIT_FAILURE);
		}
		for (std::vector<pollfd>::iterator it = _pollfds.begin(); it != _pollfds.end(); it++){
			if (it->revents == 0)
				continue;
			
			if (it->revents & POLLHUP) {
				disconnect(it->fd);
			}
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
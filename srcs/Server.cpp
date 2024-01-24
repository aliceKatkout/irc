/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 15:04:54 by mrabourd          #+#    #+#             */
/*   Updated: 2024/01/24 12:42:00 by avedrenn         ###   ########.fr       */
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
void Server::start() {
	pollfd server_fd = {_server_fd, POLLIN, 0};
	userFDs.push_back(server_fd);

	std::cout << "Server listening..." << std::endl;

	while (1) { // 1 can be changed to a boolean variable to stop the server

		// Loop waiting for incoming connects or for incoming data on any of the connected sockets.
		if (poll(userFDs.begin().base(), userFDs.size(), -1) < 0)
			throw std::runtime_error("Error while polling from fd.");

		// One or more descriptors are readable. Need to determine which ones they are.
		for (std::vector<pollfd>::iterator  it = userFDs.begin(); it != userFDs.end(); it++) {

			if (it->revents == 0)
				continue;

			if ((it->revents & POLLHUP) == POLLHUP) {
				//onClientDisconnect(it->fd);
				break;
			}

			if ((it->revents & POLLIN) == POLLIN) {

				if (it->fd == _server_fd) {
					onClientConnect();
					break;
				}

				//onClientMessage(it->fd);
			}
		}
	}
}

void Server::onClientConnect() {

	struct sockaddr_in client_address = {};
	socklen_t client_address_len = sizeof(client_address);

	int client_fd = accept(_server_fd, (struct sockaddr *) &client_address, &client_address_len);
	if (client_fd < 0)
		throw std::runtime_error("Error while accepting connection.");

	// Forcefully attaching socket to the port
	int val = 1;
	if (setsockopt(client_fd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val)))
		throw std::runtime_error("Error while setting socket options.");

	/*
	 * As requested from subject we set the socket to NON-BLOCKING mode
	 * allowing it to return any data that the system has in it's read buffer
	 * for that socket, but, it won't wait for that data.
	 */
	if (fcntl(client_fd, F_SETFL, O_NONBLOCK) == -1) {
		throw std::runtime_error("Error while setting socket to NON-BLOCKING.");
	}

	pollfd client = {client_fd, POLLIN, 0};
	userFDs.push_back(client);

	std::cout << "New client connected." << std::endl;
}

int Server::init() {

	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
		throw std::runtime_error("Error while opening socket.");

	// Forcefully attaching socket to the port
	int val = 1;
	if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val)))
		throw std::runtime_error("Error while setting socket options.");

	/*
	 * As requested from subject we set the socket to NON-BLOCKING mode
	 * allowing it to return any data that the system has in it's read buffer
	 * for that socket, but, it won't wait for that data.
	 */
	if (fcntl(sockfd, F_SETFL, O_NONBLOCK) == -1) {
		throw std::runtime_error("Error while setting socket to NON-BLOCKING.");
	}

	struct sockaddr_in serv_address = {};

	// Clear address structure, should prevent some segmentation fault and artifacts
	bzero((char *) &serv_address, sizeof(serv_address));

	/*
	 * htons() convert unsigned short int to big-endian network byte order as expected from TCP protocol standards
	 */
	serv_address.sin_family = AF_INET;
	serv_address.sin_addr.s_addr = INADDR_ANY;
	serv_address.sin_port = htons(atoi(_str_port));

	// Bind the socket to the current IP address on selected port
	if (bind(sockfd, (struct sockaddr *) &serv_address, sizeof(serv_address)) < 0)
		throw std::runtime_error("Error while binding socket.");

	// Let socket be able to listen for requests
	if (listen(sockfd, MAX_EVENTS) < 0)
		throw std::runtime_error("Error while listening on socket.");
	_server_fd = sockfd;
	return sockfd;
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
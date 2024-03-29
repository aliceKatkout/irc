/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 15:04:54 by mrabourd          #+#    #+#             */
/*   Updated: 2024/02/23 12:16:48 by avedrenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Server.hpp"

bool g_isRunning = true;

Server::Server() {
	// _handler = CmdHandler();

}

Server::Server(char *port, char *passwd) {
	if (this->setPort(port) == false)
		std::cerr << "The port is not valid!" << std::endl;
	if (this->setPasswd(passwd) == false)
		std::cerr << "The password is not valid!" << std::endl;
	_hostname = "localhost";
	_hostname = "BeachLifeStyle";

	_handler = new CmdHandler();

}

// static void displayChannels(std::vector<Channel *> c){
// 	// Server *s = user->getServer();

// 	// if (s->getChannels().size() < 1)
// 	// 	std::cout << "There are no channel remaining here" << std::endl;
// 	// std::vector<Channel *> c = s->getChannels();
// 	std::vector<Channel *>::iterator it = c.begin();
// 	for ( ; it != c.end() ; it++) {
// 		std::cout << (*it)->getName() << " channel is still in the server" << std::endl;
// 	}
// }


Server::~Server() {

	// displayChannels(_channels);
	std::vector<Channel *>::iterator itc = _channels.begin();

	for ( ; itc != _channels.end() ; itc++){
		delete (*itc);
		*itc = NULL;
	}
	_channels.clear();

	std::map<int, User *>::iterator it = _connectedUsers.begin();
	for (; it != _connectedUsers.end(); it++){
		delete it->second;
		it->second = NULL;
	}
	_connectedUsers.clear();

	delete _handler;
	_handler = NULL;

	//delete channels
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

int Server::UserMessage(int userFd){

	char buff[100];
	bzero(buff, 100);

	size_t rec = 0;

	while (!std::strstr(buff, "\r\n"))
	{
		bzero(buff, 100);
		rec = recv(userFd, buff, 100, 0);
		if (rec <= 0) // 0 = disconnected
		{
			if (errno != EWOULDBLOCK ) {
				return (-1);
			}
			if (rec == 0){
				break ;
			}
		}
		_connectedUsers[userFd]->setClientBuff(buff);
	}

	std::string msg = _connectedUsers[userFd]->getClientBuff();

	if (!msg.empty() && std::strstr(buff, "\r\n")){
		_connectedUsers[userFd]->clearClientBuff();
		return (_handler->parsing(msg, _connectedUsers[userFd]));
	}
	return (0);
}

bool Server::userIsConnected(int fd){
	if (_connectedUsers[fd] != NULL)
		return (true);
	return (false);
}

void Server::start() {
	pollfd server_fd = {_server_fd, POLLIN, 0};
	server_fd.events = POLLIN | POLLHUP | POLLERR;
	_userFDs.push_back(server_fd);

	std::cout << "Server listening..." << std::endl;
	while (g_isRunning) { // 1 can be changed to a boolean variable to stop the server
		if (!g_isRunning)
			break;
		// Loop waiting for incoming connects or for incoming data on any of the connected sockets.
		if (poll(_userFDs.begin().base(), _userFDs.size(), -1) < 0 && g_isRunning == true) {
			std::cerr << "Error while polling." << std::endl;
			break;
		}
		// One or more descriptors are readable. Need to determine which ones they are.
		for (std::vector<pollfd>::iterator it = _userFDs.begin(); it != _userFDs.end(); it++) {
			if (!g_isRunning)
				break;
			if (it->revents == 0)
				continue;

			else if ((it->revents & POLLERR) == POLLERR || (it->revents & POLLHUP) == POLLHUP)
			{
				//std::cout << "Disconnect from POLLERR or POLLHUP" << std::endl;
				UserDisconnect(it->fd);
				break;
			}

			else if ((it->revents & POLLIN) == POLLIN) {

				if (it->fd == _server_fd) {
					UserConnect();
					break;
				}

				if (UserMessage(it->fd) == -1 ){
					//std::cout << "Disconnect from USERMESSAGE == -1" << std::endl;
					UserDisconnect(it->fd);
					break;
				}

			}
		}
	}

}

void Server::userQuitAllChan(User *user){

	std::vector<Channel *> *channels = getChannels();
	if (channels == NULL)
		return ;

	std::vector<Channel *>::iterator it = channels->begin();

	for ( ; it != channels->end() ; it++){
		if ((*it) && (*it)->getUserByNick(user->getNickname()) != NULL)
			(*it)->removeUser(user);
	}
}

void Server::UserDisconnect(int fd){
	if (_connectedUsers.size() < 1){
		return ;
	}
	if (userIsConnected(fd) == false){
		return;
	}

	userQuitAllChan(_connectedUsers.at(fd));

	User *userToDelete = _connectedUsers.at(fd);
	_connectedUsers.erase(fd);

	std::vector<pollfd>::iterator it = _userFDs.begin();
	for (; it != _userFDs.end(); it++)
	{
		if (it->fd == fd)
		{
			_userFDs.erase(it);
			close(fd);
			break;
		}
	}
	delete userToDelete;
	// userToDelete = NULL;
}

void Server::UserConnect() {

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
	client.events = POLLIN | POLLHUP | POLLERR;
	_userFDs.push_back(client);

	User *newUser = new User(client_fd, this); // create user;

	//newUser->askPasswd();

	this->_connectedUsers.insert(std::pair<int, User *>(client_fd, newUser));

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

std::string Server::getHostname() const {
	return _hostname;
}

Channel *	Server::createChannel(std::string channelName, User *user){

	Channel *newChannel = new Channel(channelName, "");
	newChannel->setOperators(user, true);
	_channels.push_back(newChannel);
	return (newChannel);
}

std::vector<Channel *> *Server::getChannels(){
	return (&_channels);
}

Channel *Server::getLastChannel(){
	return (_channels.back());
}

bool Server::checkPassword(std::string &passwd){
	if (_passwd.compare(passwd) == 0) // -1 to remove \n
		return (true);
	return (false);
}

std::map<int, User *> *Server::getConnectedUsers(){
	return (&_connectedUsers);
}

User *Server::findUserNick(std::string nick){
	std::map<int, User *>::iterator it = _connectedUsers.begin();
	for (; it != _connectedUsers.end(); it++){
		if (it->second->getNickname() == nick)
			return (it->second);
	}
	return (NULL);
}

void	Server::broadcastQuit(std::string message, User *user){

	std::map<int, User *> *connectedUsers = getConnectedUsers();
	std::map<int, User *>::iterator it = connectedUsers->begin();

	for ( ; it != connectedUsers->end(); it++) {

		if (it->first != user->getFd()){
			it->second->reply("QUIT " + message);
		}
	}
}

Channel *Server::findChannelByName(std::string channelName){
	if (channelName == "")
		return NULL;

	std::vector<Channel *>::iterator it = getChannels()->begin();

	for (; it != getChannels()->end() ; it++){
		if ((*it)->getName() == channelName)
			return (*it);
	}
	return (NULL);
}
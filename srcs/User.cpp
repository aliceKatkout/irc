/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 15:42:27 by mrabourd          #+#    #+#             */
/*   Updated: 2024/02/12 16:04:05 by avedrenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/User.hpp"

User::User(int fd, Server *server): _fd(fd), _server(server) {
	_nickname = "";
	_username = "";
	_realname = "";
	_good_pass = false;
	if (_server)
		_hostname = _server->getHostname();
	else
		_hostname = "";
	_is_registered = false;
	_state = HANDSHAKE;


	// if (server->getChannel().size() == 0){
	// 	server->createChannel("#general");

	// 	Channel *newChann = server->getLastChannel();
	// 	this->addChannel(newChann);

	// 	// this->reply("003 " + this->getNickname() + " :joins channel" + this->getChannel().back()->getName());
	// }

}

User::~User(){

}

bool User::operator==(const User &rhs) const {
	return _fd == rhs._fd;
}

void User::addChannel(Channel *channel ){
	_channels.push_back(channel);
}

std::string User::getPrefix() const {
	return _nickname + (_username.empty() ? "" : "!" + _username) + (_hostname.empty() ? "" : "@" + _hostname);
}

void User::write(const std::string &message) const {

	//std::cout << "-> " << message << std::endl;

	std::string buffer = message + "\r\n";
	if (send(_fd, buffer.c_str(), buffer.length(), 0) < 0)
		throw std::runtime_error("Error while sending message to User.");
}

void User::reply(const std::string &reply) {
	write(":" + getPrefix() + " " + reply);
}


int User::getFd() const {
    return (this->_fd);
}

std::string User::getNickname() const {
	return (this->_nickname);
}

std::string User::getUsername() const {
	return (this->_username);
}

bool User::getGoodPass() const {
	return (this->_good_pass);
}

Server *User::getServer() const {
	return (this->_server);
}

std::vector<Channel *> User::getChannel() {
	return (this->_channels);
}

void User::setNickname(std::string nickname) {
	this->_nickname = nickname;
}

void User::setUsername(std::string username) {
	if (username.empty())
		return;
	this->_username = username;
}

void User::setRealname(std::string realname) {
	this->_realname = realname;
}

void User::setGoodPass(bool good_pass) {
	this->_good_pass = good_pass;
}

bool User::getIsRegistered() const {
	return (this->_is_registered);
}

void User::setIsRegistered(bool is_registered) {
	this->_is_registered = is_registered;
}

UserState User::findState() {
	if (_nickname.empty() || _username.empty() || !_good_pass)
		return HANDSHAKE;
	if (_good_pass && !_is_registered)
		return LOGIN;
	if (_is_registered)
		return ACTIVE;
	return DISCONNECTED;

}

UserState User::getState() const {
	return _state;
}

void User::setState(UserState state) {
	_state = state;
}

void User::welcome() {
	if (_state != LOGIN || _username.empty() || _realname.empty() || _nickname.empty())
		return;
	_state = ACTIVE;
	_is_registered = true;

	reply("001 " + getNickname() + " :✨ Welcome to the Internet Relay Network mon ptit pote ✨");

	//char message[100];
	//sprintf(message, "%s:%d is now known as %s.", _hostname.c_str(), _port, _nickname.c_str());

}

void User::setInvisible(bool invisible) {
	_invisible = invisible;
}

Channel *User::getOneChannel(std::string name) {
	std::vector<Channel *>::iterator it = _channels.begin();
	for ( ; it != _channels.end(); it++) {
		if ((*it)->getName() == name)
			return (*it);
	}
	return (NULL);
}

User *User::getUserByNick(std::string nickname) {
	std::map<int, User *> connectedUsers = getServer()->getConnectedUsers();
	for (std::map<int, User *>::iterator it = connectedUsers.begin(); it != connectedUsers.end(); it++) {
		if (it->second->getNickname() == nickname)
			return (it->second);
	}
	return (NULL);
}
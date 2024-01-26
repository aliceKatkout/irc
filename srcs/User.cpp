/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabourd <mrabourd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 15:42:27 by mrabourd          #+#    #+#             */
/*   Updated: 2024/01/26 18:23:19 by mrabourd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/User.hpp"

User::User(int fd, Server *server): _fd(fd), _server(server) {
	_nickname = "";
	_username = "";
	_good_pass = false;
	if (_server)
		_hostname = _server->getHostname();
	else
		_hostname = "";
	_is_registered = false;
}

User::~User(){

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
	return (this->_channel);
}

void User::setNickname(std::string nickname) {
	this->_nickname = nickname;
}

void User::setUsername(std::string username) {
	this->_username = username;
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
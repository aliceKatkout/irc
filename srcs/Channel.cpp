/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabourd <mrabourd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 18:21:49 by mrabourd          #+#    #+#             */
/*   Updated: 2024/02/21 17:32:22 by mrabourd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Channel.hpp"



Channel::Channel(std::string name, std::string password) : _name(name), _k(password) {
    _l = 100;
	_i = false;
	topicSet = false;
	_t = true;
}

Channel::~Channel() {
	// std::cout << "delete channel." << std::endl;
}

bool	Channel::isUserOperator(User * user) {
	if (std::find(_operators.begin(), _operators.end(), user) == _operators.end()){
		// std::cout << "false" << std::endl;
		return (false);
	}
	// std::cout << "true" << std::endl;
	return (true);
}

void    Channel::setOperators(User *toAdd, bool b){
	if (b == true && isUserOperator(toAdd) == false)
		_operators.push_back(toAdd);
	else if (b == false && isUserOperator(toAdd))
		_operators.erase(std::find(_operators.begin(), _operators.end(), toAdd));
}

void	Channel::setTopicProtection(bool b){
	this->_t = b;
}

bool	Channel::getTopicProtection() const {
	return (this->_t);
}

void   Channel::removeUser(User *user){
	std::vector<User *>::iterator it = std::find(_joinedUsers.begin(), _joinedUsers.end(), user);
	if (it != _joinedUsers.end())
		_joinedUsers.erase(it);
}

User	*Channel::getUserByNick(std::string nickname){
	std::vector<User *>::iterator it = _joinedUsers.begin();
	for (; it != _joinedUsers.end(); it++){
		if ((*it)->getNickname() == nickname)
			return (*it);
	}
	return (NULL);
}

void    Channel::setLimit(int limit){
	this->_l = limit;
	std::cout << "limit inside setLimit: " << _l << std::endl;
}

void	Channel::setInviteOnly(bool b){
	this->_i = b;
}

void	Channel::setTopic(std::string topic){
	this->_topic = topic;
	topicSet = true;
}

void	Channel::setInvitedUsers(std::string username){
	this->_invitedUsers.push_back(username);
}

std::string Channel::getName() const {
	// std::cout << this->_name << std::endl;
	return (this->_name);
}

std::string Channel::getPassword() const {
	return (this->_k);
}

int    Channel::getLimit() const {
	return (_l);
}

bool Channel::getInviteOnly() const {
	return (this->_i);
}

std::vector<User *> Channel::getUsers() {
	return (_joinedUsers);
}

std::vector<User *>		Channel::getOperators(){
	return (this->_operators);
}

std::string Channel::getTopic() {
	return (this->_topic);
}

std::vector<std::string> Channel::getInvitedUsers(){
	return (this->_invitedUsers);
}


bool	Channel::addUser(User *user, std::string password) {
	if (!this->_k.empty() && this->_k.compare(password) != 0){
		user->reply("475 " + user->getNickname() + " " + _name + " :Cannot join channel (+k)");
		return (false);
	}
	std::cout << "inside adduser" << std::endl;
	std::vector<std::string> u = this->getInvitedUsers();
	if (this->getInviteOnly() == true){
		if (std::find(u.begin(), u.end(), user->getNickname()) == u.end()) {
			user->reply("473 " + user->getNickname() + " " + _name + " :Cannot join channel (+i)");
			return (false);
		}
	}
	std::cout << "size : " << this->_joinedUsers.size() << std::endl;
	std::cout << "limit 1 : " << getLimit() << std::endl;
	if (this->_joinedUsers.size() >= (size_t)getLimit()){
		std::cout << "size : " << this->_joinedUsers.size() << std::endl;
		std::cout << "limit 2: " << getLimit() << std::endl;
		user->reply("471 " + user->getNickname() + " " + _name + " :Cannot join channel (+l)");
		return (false);
	}

	std::vector<Channel *> *vecChan = user->getChannel();

	if ((*vecChan).size() >= 10) {
		user->reply("405 " + _name + " :Cannot join channel (Too many joined channels)");
		return (false);
	}

	this->_joinedUsers.push_back(user);
	return (true);

}



bool	Channel::partUser(User *user) {

	if (isUserOperator(user) == true)
		setOperators(user, false);

	std::vector<User *>::iterator it = _joinedUsers.begin();
	for (; it != _joinedUsers.end(); it++) {
		if (*it == user){
			_joinedUsers.erase(it);
			*it = NULL;
			break ;
			// if (_joinedUsers.size() == 0)
			// 	delete this; // ?? ca marche ca ?
		}
	}

	/* remove: déplace les éléments indésirables à la fin de la chaîne,
	puis retourne un itérateur pointant vers le début de la séquence
	contenant les éléments non supprimés.*/

	// _joinedUsers.erase(std::remove(_joinedUsers.begin(), _joinedUsers.end(),
	// 	user), _joinedUsers.end());

	if (_joinedUsers.empty() == true){
		return (false); // remove the channel
	}



	return (true);

}

void	Channel::setName(std::string name){
	this->_name = name;
}

void	Channel::setPassword(std::string password){
	this->_k = password;
}

void	Channel::broadcastChan(std::string message, User *user){
	for (size_t i = 0; i < getUsers().size(); i++)
	{
		if (getUsers()[i] != user)
			getUsers()[i]->write(":" + user->getPrefix() + " " + message);
	}
}
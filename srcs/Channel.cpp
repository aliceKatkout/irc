/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 18:21:49 by mrabourd          #+#    #+#             */
/*   Updated: 2024/02/23 15:05:59 by avedrenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Channel.hpp"



Channel::Channel(std::string name, std::string password) : _name(name), _k(password) {
    _l = 100;
	_i = false;
	topicSet = false;
	_t = true;
	_joinedUsers = new std::vector<User *>;
	_nbUsers = 0;
}

Channel::~Channel() {
	delete _joinedUsers;
}

bool	Channel::isUserOperator(User * user) {
	if (std::find(_operators.begin(), _operators.end(), user) == _operators.end()){
		return (false);
	}
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


// static void moveItemToBack(std::vector<User *>& v, size_t itemIndex)
// {
//    User * tmp(v[itemIndex]);
//    v.erase(v.begin() + itemIndex);
//    v.push_back(tmp);
// }

void   Channel::removeUser(User *user){
	std::vector<User *>::iterator it = _joinedUsers->begin();
	for (; it != _joinedUsers->end(); it++){
		if (*it && *it == user) {
			_joinedUsers->erase(it);
			*it = NULL;
			break;
		}
	}

	user->setNbOfChannels(user->getNumberOfChannels() - 1);
	setNbUsers(getNbUsers() - 1);
}

User	*Channel::getUserByNick(std::string nickname){
	std::vector<User *>::iterator it = _joinedUsers->begin();
	for (; it != _joinedUsers->end(); it++){
		if ((*it) && (*it)->getNickname() == nickname)
			return (*it);
	}
	return (NULL);
}

void    Channel::setLimit(int limit){
	this->_l = limit;
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

std::vector<User *> *Channel::getUsers() {
	return (_joinedUsers);
}

std::vector<User *>		*Channel::getOperators(){
	return (&this->_operators);
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

	std::vector<std::string> u = this->getInvitedUsers();
	if (this->getInviteOnly() == true){
		if (std::find(u.begin(), u.end(), user->getNickname()) == u.end()) {
			user->reply("473 " + user->getNickname() + " " + _name + " :Cannot join channel (+i)");
			return (false);
		}
	}

	if ((*_joinedUsers).size() >= (size_t)getLimit()){
		user->reply("471 " + user->getNickname() + " " + _name + " :Cannot join channel (+l)");
		return (false);
	}

	if (user->getNumberOfChannels() >= 10) {
		user->reply("405 " + _name + " :Cannot join channel (Too many joined channels)");
		return (false);
	}

	_joinedUsers->push_back(user);
	setNbUsers(getNbUsers() + 1);
	user->setNbOfChannels(user->getNumberOfChannels() + 1);
	return (true);

}

bool	Channel::partUser(User *user) {

	if (isUserOperator(user) == true) {
		setOperators(user, false);
	}


	std::vector<User *>::iterator it = std::find(_joinedUsers->begin(), _joinedUsers->end(), user);
	if (it != _joinedUsers->end())
	{
		User * tmp(*it);
		_joinedUsers->erase(it);
		_joinedUsers->push_back(tmp);
	}

	removeUser(user);

	if (getUsers()->empty() == true ||  getNbUsers() < 1) {
		return (false); // remove the channel
	}
	return (true);

}

void	Channel::setNbUsers(int nb){
	this->_nbUsers = nb;
}

int		Channel::getNbUsers() const {
	return (_nbUsers);
}

void	Channel::setName(std::string name){
	this->_name = name;
}

void	Channel::setPassword(std::string password){
	this->_k = password;
}

void	Channel::broadcastChan(std::string message, User *user){
	if (getNbUsers() < 1)
		return ;

	std::vector<User *> users = *getUsers();

	std::vector<User *>::iterator it = getUsers()->begin();
	for ( ; it != getUsers()->end(); it++) {
		if (*it != NULL && *it != user){
			(*it)->write(":" + user->getPrefix() + " " + message);
		}
	}


	// for (int i = 0; i < getNbUsers();  i++)
	// {
	// 	if (users[i] != NULL && users[i] != user){
	// 		std::cout << "Broadcasting to " << users[i]->getNickname() << std::endl;
	// 		users[i]->write(":" + user->getPrefix() + " " + message);
	// 	}
	// }

}
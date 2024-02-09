/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabourd <mrabourd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 18:21:49 by mrabourd          #+#    #+#             */
/*   Updated: 2024/02/09 17:06:31 by mrabourd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Channel.hpp"

Channel::Channel(std::string name, std::string password) : _name(name), _k(password) {
    _l = 100;
	_i = false;
	topicSet = false;
}

Channel::~Channel() {
	std::cout << "delete channel." << std::endl;
    delete (this);
}

void    Channel::setOperator(User *user, bool b){
	if (b == true)
		this->_operator = user;
	else
		this->_operator = NULL;
}

void    Channel::setLimit(size_t limit){
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
	// std::cout << this->_name << std::endl;
	return (this->_name);
}

std::string Channel::getPassword() const {
	return (this->_k);
}

size_t    Channel::getLimit() const {
	return (this->_l);
}

bool Channel::getInviteOnly() const {
	return (this->_i);
}

std::vector<User *> Channel::getUsers() {
	return (_joinedUsers);
}

User *		Channel::getOperator(){
	return (this->_operator);
}

std::string Channel::getTopic() {
	return (this->_topic);
}

std::vector<std::string> Channel::getInvitedUsers(){
	return (this->_invitedUsers);
}


bool	Channel::addUser(User *user, std::string password) {
	if (!this->_k.empty() && this->_k.compare(password) != 0){
		user->reply("475 " + _name + " :Cannot join channel (+k)");
		return (false);
	}

	std::vector<std::string> u = this->getInvitedUsers();
	if (this->getInviteOnly() == true){
		if (std::find(u.begin(), u.end(), user->getNickname()) == u.end()) {
			user->reply("473 " + user->getNickname() + " " + _name + " :Cannot join channel (+i)");
			//user->write(":" + user->getNick() + " 473 " + _name + " :Cannot join channel (+i)\r\n");
			//(":localhost 473 " + user + " #" + channel +  " :Cannot join channel (+i)\r\n")

			return (false);
		}
	}

	if (this->_joinedUsers.size() >= this->_l ){
		user->reply("471 " + _name + " :Cannot join channel (+l)");
		return (false);
	}

	if (user->getChannel().size() >= 10) {
		user->reply("405 " + _name + " :Cannot join channel (+l)");
		return (false);
	}

	this->_joinedUsers.push_back(user);
	this->_l++;
	return (true);

}



bool	Channel::kickUser(User *user) {

	if (this->_operator == user) {
		std::cout << "remove user from being operator" << std::endl;
		this->_operator = NULL;
	}

	std::vector<User *>::iterator it = _joinedUsers.begin();
	for (; it != _joinedUsers.end(); it++) {
		if (*it == user){
			std::cout << "erase " << (*it)->getNickname() << " from list of users..." << std::endl;
			_joinedUsers.erase(it);
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
		std::cout << "There is no one left in this channel" << std::endl;
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
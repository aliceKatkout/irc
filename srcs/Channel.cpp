/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 18:21:49 by mrabourd          #+#    #+#             */
/*   Updated: 2024/02/06 12:31:01 by avedrenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Channel.hpp"

Channel::Channel(std::string name, std::string password) : _name(name), _k(password) {
    _l = 10;
	_i = false;
	topicSet = false;
}

Channel::~Channel() {
	std::cout << "delete channel." << std::endl;
    delete (this);
}

void    Channel::setOperator(User *user){
	this->_operator = user;
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

bool	Channel::addUser(User *user) {
	if (this->_joinedUsers.size() < this->_l){
		this->_joinedUsers.push_back(user);
		this->_l++;
		return true;
	}
	return (false);
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
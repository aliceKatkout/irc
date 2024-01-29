/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabourd <mrabourd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 18:21:49 by mrabourd          #+#    #+#             */
/*   Updated: 2024/01/29 19:13:24 by mrabourd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Channel.hpp"

Channel::Channel(std::string name, std::string password) : _name(name), _k(password) {
    
}

Channel::~Channel() {
    
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

bool	Channel::addUser(User *user) {
	if (this->_joinedUsers.size() < this->_l){
		this->_joinedUsers.push_back(user);
		this->_l++;
		return true;
	}
	return (false);
}

bool	Channel::kickUser(User *user) {
	// std::vector<User *>::iterator it = _joinedUsers.begin();
	// for (; it != _joinedUsers.end(); it++) {
	// 	if (*it == user){
	// 		delete *it;
	// 		if (_joinedUsers.size() == 0)
	// 			delete this; // ?? ca marche ca ?
	// 	}
	// }

	/* remove: déplace les éléments indésirables à la fin de la chaîne,
	puis retourne un itérateur pointant vers le début de la séquence 
	contenant les éléments non supprimés.*/
	
	_joinedUsers.erase(std::remove(_joinedUsers.begin(), _joinedUsers.end(),
		user), _joinedUsers.end());
	
	if (this->_operator == user) {
		// ou que: _joinedUsers.size() == 0
		// supprimer le channel ?
		return (true);
	}
	return (true);
	
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabourd <mrabourd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 15:42:27 by mrabourd          #+#    #+#             */
/*   Updated: 2024/01/25 17:04:56 by mrabourd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/User.hpp"

User::User(int fd): _fd(fd) {
	_nickname = "";
	_username = "";
	_good_pass = false;
}

User::~User(){

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

void User::setNickname(std::string nickname) {
	this->_nickname = nickname;
}

void User::setUsername(std::string username) {
	this->_username = username;
}

void User::setGoodPass(bool good_pass) {
	this->_good_pass = good_pass;
}

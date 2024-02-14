/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabourd <mrabourd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 14:23:18 by avedrenn          #+#    #+#             */
/*   Updated: 2024/02/14 15:52:14 by mrabourd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Command.hpp"

/* void Server::nickCommand(int const fd, std::vector<std::string> cmd_parts)
{
	std::string nick_name = ft_strtok(cmd_parts[2]);
	std::string old_name = "";
	if (nick_name.empty())
		_users[fd]->setSendBuff(ERR_NONICKNAMEGIVEN(_users[fd]->getNickName()));
	else if (!validNick(nick_name))
		_users[fd]->setSendBuff(ERR_ERRONEUSNICKNAME(_users[fd]->getNickName(), nick_name));
	else if (isDupNick(nick_name))
		_users[fd]->setSendBuff(ERR_NICKNAMEINUSE(_users[fd]->getNickName(), nick_name));
	else if (!_users[fd]->getIsRegistered())
		_users[fd]->setNickName(nick_name);
	else {
		if (_users[fd]->getIsRegistered()) {
			std::cout << "[S] Nickname changed." << std::endl;
			old_name = _users[fd]->getNickName();
			_users[fd]->setNickName(nick_name);
		}
	}
	_users[fd]->setSendBuff(":" + old_name + "!" + _users[fd]->getUserName() + "@localhost NICK " + nick_name + "\r\n");
}

bool Server::validNick(std::string nick_name)
{
	int i = 0;
	while (nick_name[i]) {
		if ((!isalnum(nick_name[i]) && (nick_name[i] != '-') && (nick_name[i] != '_')) || i > 8)
			return false;
		i++;
	}
	if (nick_name == "IRCSavvy")
		return false;
	return true;
}

bool Server::isDupNick(std::string nick_name)
{
	for (std::map<int, User *>::iterator it = _users.begin(); it != _users.end(); it++ ) {
		if (it->second->getNickName() == nick_name)
			return true;
	}
	return false;
} */

static bool isDupNick(std::string nick_name, std::map<int, User *> users)
{
	for (std::map<int, User *>::iterator it = users.begin(); it != users.end(); it++ ) {
		if (it->second->getNickname() == nick_name)
			return true;
	}
	return false;
}

void NickCmd::execute(User *user, std::vector<std::string> args) {

	std::string oldNick = user->getNickname();

	if (args.size() < 2)
		return (user->reply("431 NICK:No nickname given"));

	std::string newNick = args[1];
	if (newNick.size() > 15)
		return (user->reply("432 NICK " + newNick + " :Erroneous nickname (too long)"));
	if (newNick.find_first_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ") == std::string::npos)
		return (user->reply("432 NICK " + newNick + " :Erroneous nickname (invalid character)"));
	if (isDupNick(newNick, user->getServer()->getConnectedUsers())){
		std::cout << "newNick: " << newNick << std::endl;
		// user->reply("433 NICK " + newNick +  " :Nickname is owned by " + user->getServer()->findUserNick(newNick)->getUsername());
		newNick += "_";
	}
	user->reply("NICK :" + newNick );
	user->setNickname(newNick);
}

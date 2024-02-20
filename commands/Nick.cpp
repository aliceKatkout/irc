/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabourd <mrabourd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 14:23:18 by avedrenn          #+#    #+#             */
/*   Updated: 2024/02/20 18:06:37 by mrabourd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Command.hpp"


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
	if (isDupNick(newNick, (*user->getServer()->getConnectedUsers())))
		newNick += "_";
	if (user->getServer()->findUserNick(newNick) != NULL)
		return (user->reply("433 NICK " + newNick +  " :Nickname is owned by " + user->getServer()->findUserNick(newNick)->getUsername()));
	user->reply("NICK :" + newNick );
	user->setNickname(newNick);
}

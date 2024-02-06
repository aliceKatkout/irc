/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PrivMsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 14:44:42 by avedrenn          #+#    #+#             */
/*   Updated: 2024/02/06 16:18:04 by avedrenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Command.hpp"

void PrivMsgCmd::execute(User *user, std::vector<std::string> args) {
	if (args.size() < 2)
	{
		user->reply("411 PRIVMSG :No recipient given (PRIVMSG)");
		return ;
	}
	if (args.size() < 3)
	{
		user->reply("412 PRIVMSG :No text to send");
		return ;
	}
	std::string target = args[1];
	std::string message = "";
	for (size_t i = 2; i < args.size(); i++)
	{
		message += args[i];
		if (i + 1 < args.size())
			message += " ";
	}
	if (target[0] == '#' || target[0] == '&')
	{
		Channel *chan = user->getOneChannel(target);
		if (chan == NULL)
		{
			user->reply("401 " + target + " :No such nick/channel");
			return ;
		}
		if (chan->getUsers().size() == 0)
		{
			user->reply("411 PRIVMSG :No recipient given (PRIVMSG)");
			return ;
		}
		for (size_t i = 0; i < chan->getUsers().size(); i++)
		{
			if (chan->getUsers()[i] != user)
				chan->getUsers()[i]->write(":" + user->getPrefix() + " PRIVMSG " + target + " :" + message);
		}
	}
	else
	{
		User *targetUser = user->getUserByNick(target);
		if (targetUser == NULL)
		{
			user->reply("401 " + target + " :No such nick/channel");
			return ;
		}
		targetUser->write(":" + user->getPrefix() + " PRIVMSG " + target + " :" + message);
	}

}
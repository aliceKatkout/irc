/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 14:23:18 by avedrenn          #+#    #+#             */
/*   Updated: 2024/02/02 15:57:22 by avedrenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Command.hpp"

void NickCmd::execute(User *user, std::vector<std::string> args) {
	std::string oldNick = user->getNickname();

	if (args.size() < 2)
	{
		user->reply("431 :No nickname given");
		return ;
	}
	if (args[1].size() > 9)
	{
		user->reply("432 " + args[1] + " :Erroneous nickname");
		return ;
	}
	if (args[1].find_first_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ") == std::string::npos)
	{
		user->reply("432 " + args[1] + " :Erroneous nickname");
		return ;
	}
	if (user->getServer()->getConnectedUsers()->getNickname() == args[1])
	{
		user->reply("NICK " + args[1] + " :Nickname is already in use");
		return ;
	}
	user->reply("NICK " + args[1] +  " Nickname set to " + args[1]);
	user->setNickname(args[1]);
}
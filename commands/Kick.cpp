/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 14:04:16 by avedrenn          #+#    #+#             */
/*   Updated: 2024/02/14 12:59:46 by avedrenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Command.hpp"



void KickCmd::execute(User *user, std::vector<std::string> args) {
	std::cout << args[1] << std::endl;
	if (args.size() < 3)
		return( user->reply("461 KICK :Not enough parameters" ));

	Channel *chan = ChannelExistsAlready(user, args[1]);
	if (!chan)
		return (user->reply("403 KICK "+ args[1] +" :No such channel"));

	if (!chan->isUserOperator(user))
		return (user->reply("KICK " + chan->getName() + " :You are not an operator"));

	User *u = chan->getUserByNick(args[2]);
	if (!u)
		return (user->reply("442 KICK " + chan->getName() + " :User not on that channel"));
	if (u->getNickname() == user->getNickname())
		return (user->reply("442 KICK " + chan->getName() +" :Can't kick yourself"));

	user->reply("KICK " + chan->getName() + " " + u->getNickname() + " :Kicked by " + user->getNickname());
	chan->broadcastChan(" KICK " + chan->getName() + " " + u->getNickname() + " :Kicked by " + user->getNickname(), user);

	chan->removeUser(u);
}
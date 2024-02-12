/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 14:04:16 by avedrenn          #+#    #+#             */
/*   Updated: 2024/02/12 16:36:05 by avedrenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Command.hpp"



void KickCmd::execute(User *user, std::vector<std::string> args) {
	std::cout << args[1] << std::endl;
	if (args.size() < 3)
		return( user->reply("KICK :Not enough args" ));

	Channel *chan = ChannelExistsAlready(user, args[1]);
	if (!chan)
		return (user->reply("Kick invalid chan name"));

	if (!chan->isUserOperator(user))
		return (user->reply("Kick not an operator"));

	std::cout << "kick user: " << args[2] << std::endl;

	User *u = chan->getUserByNick(args[2]);
	if (!u)
		return (user->reply("Kick user name is not in the channel"));
	if (u->getNickname() == user->getNickname())
		return (user->reply("Kick cannot kick yourself"));

	user->reply("KICK " + chan->getName() + " " + u->getNickname() + " :Kicked by " + user->getNickname());
	chan->broadcastChan(" KICK " + chan->getName() + " " + u->getNickname() + " :Kicked by " + user->getNickname(), user);

	chan->removeUser(u);
}
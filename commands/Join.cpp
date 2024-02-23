/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 18:36:49 by mrabourd          #+#    #+#             */
/*   Updated: 2024/02/23 13:51:53 by avedrenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Command.hpp"

// ADD RESTRICTION MODE +i
void JoinCmd::execute(User *user, std::vector<std::string> args){

	if (args.size() < 2)
	{
		user->reply("461 JOIN :Not enough parameters");
		return ;
	}

	std::string channelName = *(args.begin() + 1);

    Channel *newChannel = user->getServer()->findChannelByName(channelName);

	if (newChannel == NULL){
		newChannel = user->getServer()->createChannel(channelName, user);
	}
	std::string password = "";
	if (args.size() > 2)
		password = *(args.begin() + 2);

	if (!newChannel->addUser(user, password)){
		return ;
	}
	user->reply("JOIN " + newChannel->getName());
	if ((*newChannel->getUsers()).size() > 1){
		if (newChannel->getTopic() != "")
			user->reply("332 " + user->getNickname() + " " + channelName + " :" + newChannel->getTopic());
		user->reply("353 " + user->getNickname() + " = " + channelName + " " + user->getNickname() + " :@" + user->getUsername());
		newChannel->broadcastChan("JOIN " + channelName + " " + user->getNickname(), user);
	}
}

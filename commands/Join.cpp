/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 18:36:49 by mrabourd          #+#    #+#             */
/*   Updated: 2024/02/12 14:43:49 by avedrenn         ###   ########.fr       */
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

    Channel *newChannel = ChannelExistsAlready(user, args.back());
	if (newChannel != NULL){
		std::cout << "Channel found!" << std::endl;
	}
	else {
		std::cout << "Channel not found. Creating new channel..." << std::endl;
		newChannel = user->getServer()->createChannel(channelName, user);
	}
	std::string password = "";
	if (args.size() > 2)
		password = *(args.begin() + 2);
	if (!newChannel->addUser(user, password)){
		std::cout << "User not added to chan" << std::endl;
		// user->reply("PART " + *(args.begin()+1) + " " + "Impossible to join channel");
		return ;
	}
	std::cout << "user added" << std::endl;
	user->addChannel(newChannel);
	user->reply("JOIN " + *(args.begin()+1));
	if (newChannel->getUsers().size() > 1){
		// newChannel->broadcastChan("332 " + channelName + " :" + newChannel->getTopic(), user);
		user->reply("353 " + channelName + " :" + user->getNickname());
		newChannel->broadcastChan("JOIN " + channelName + " " + user->getNickname(), user);
		// user->reply("332 " + newChannel->getName() + " :" +  newChannel->getTopic());
		std::cout << "Topic is :"<<  newChannel->getTopic() << std::endl;
	}
	// user->reply("332 " + *(args.begin()+1) + newChannel->getTopic());

// CmdHandler::parsing -> a faire

    /*
    Si channel existe deja :
        -si ne depasse pas la taille limit de users
         && le user n'est pas banned du channel
         && user a le droit de join (check les 'modes')
         && user pas deja dans 10 autres channels
            -> server envoie msg aux autres users du channel avec prefix
            -> et envoie msg au user qui a joined
            -> envoie un 'MODE' msg avec les odes du chann
            -> si topic, evoie RPL_TOPIC et RPL_TOPICTIME numerics
            -> envoie RPL_NAMREPLY




    Si n'existe pas :
        creer channel, avec ou sans password
    */
}

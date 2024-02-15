/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabourd <mrabourd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 12:51:49 by mrabourd          #+#    #+#             */
/*   Updated: 2024/02/15 13:59:16 by mrabourd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Command.hpp"

/*
-virer le user du channel via le serveur
-si c'etait le dernier user, delete le channel
-virer le channel de la liste des channel dans le user
*/

static void displayChannels(std::vector<Channel *> c){
	// Server *s = user->getServer();

	// if (s->getChannel().size() < 1)
	// 	std::cout << "There are no channel remaining here" << std::endl;
	// std::vector<Channel *> c = s->getChannel();
	std::vector<Channel *>::iterator it = c.begin();
	for ( ; it != c.end() ; it++) {
		std::cout << (*it)->getName() << " channel is still in the server" << std::endl;
	}
}

void PartCmd::execute(User *user, std::vector<std::string> args) {

	std::string channelName = *(args.begin()+1);

	Channel *channel;

	// Server *s = user->getServer();
	std::vector<Channel *> *c = user->getServer()->getChannel();
	std::vector<Channel *>::iterator its = c->begin();
	// std::vector<Channel *>::iterator it = user->getServer()->getChannel().begin() ;

	std::string reason;

	if (args.size() > 2) {
		std::vector<std::string>::iterator it = (args.begin()+2);

		for (; it != args.end(); it++){
			reason = reason + (*it) + " ";
		}
	}

	for (; its != c->end(); its++){
		if ((*its)->getName() == channelName){
			std::cout << channelName << " has to kick " << user->getNickname() << " from its list" << std::endl;
			channel = (*its);
			user->reply("PART " + channel->getName() + " " + reason);
			channel->broadcastChan("PART " + channel->getName() + " " + reason, user);
			if (channel->partUser(user) == false){
				c->erase(its);
				c->clear();
				break;
			}
		}
	}

	if (c->empty() == true)
		std::cout << "There is no channel left in this server" << std::endl;


	displayChannels(*c);
}
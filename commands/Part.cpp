/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 12:51:49 by mrabourd          #+#    #+#             */
/*   Updated: 2024/02/12 15:28:30 by avedrenn         ###   ########.fr       */
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
	std::cout << "channel to get out from: " << channelName << std::endl;

	// Server *s = user->getServer();
	std::vector<Channel *> *c = user->getServer()->getChannel();
	std::vector<Channel *>::iterator its = c->begin();
	// std::vector<Channel *>::iterator it = user->getServer()->getChannel().begin() ;

	for (; its != c->end(); its++){
		if ((*its)->getName() == channelName){
			std::cout << channelName << " has to kick " << user->getNickname() << " from its list" << std::endl;
			if ((*its)->partUser(user) == false){
				std::cout << " channel to erase: " << (*its)->getName() << std::endl;
				c->erase(its);
				c->clear();
				std::cout << "Channel " << (*its)->getName()  << " deleted successfully " << std::endl;
				break;
			}
		}
	}

	if (c->empty() == true)
		std::cout << "There is no channel left in this server" << std::endl;

	/* pas besoin car pointeur sur ce channel deja deleted ?
	-> remove channel from list of channels in the user list of channels */
	// std::vector<Channel *> channel = user->getChannel();
	// std::vector<Channel *>::iterator itu = c.begin();

	// for (; itu != c.end(); itu++){
	// 	if ((*itu)->getName() == channelName){
	// 		c.erase(*its);
	// 	}
	// }

	/* ADD REASON WHY LEAVES THE CHANNEL */

	std::string reason;

	if (args.size() > 2) {
		std::vector<std::string>::iterator it = (args.begin()+3);

		for (; it != args.end(); it++){
			reason = reason + (*it) + " ";
		}
	}
	user->reply("PART " + *(args.begin()+1) + " " + reason);

	displayChannels(*c);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 12:51:49 by mrabourd          #+#    #+#             */
/*   Updated: 2024/02/23 15:05:23 by avedrenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Command.hpp"

/*
-virer le user du channel via le serveur
-si c'etait le dernier user, delete le channel
-virer le channel de la liste des channel dans le user
*/

// static void displayChannels(std::vector<Channel *> c){
// 	// Server *s = user->getServer();

// 	// if (s->getChannels().size() < 1)
// 	// 	std::cout << "There are no channel remaining here" << std::endl;
// 	// std::vector<Channel *> c = s->getChannels();
// 	std::vector<Channel *>::iterator it = c.begin();
// 	for ( ; it != c.end() ; it++) {
// 		std::cout << (*it)->getName() << " channel is still in the server" << std::endl;
// 	}
// }


void PartCmd::execute(User *user, std::vector<std::string> args) {

	std::string channelName = *(args.begin()+1);
	std::string reason = "";

	if (channelName.empty()){
		user->reply(ERR_NEEDMOREPARAMS(user->getNickname(), "PART"));
	}

	if (args.size() > 2) {
		std::vector<std::string>::iterator it = (args.begin()+2);
		for (; it != args.end(); it++){
			reason = reason + (*it) + " ";
		}
	}

	std::vector<Channel *> *c = user->getServer()->getChannels();
	std::vector<Channel *>::iterator its = c->begin();

	for (; its != c->end(); its++){
		if ((*its) && (*its)->getName() == channelName){
			user->reply("PART " + channelName + " " + reason);
			if ((*its)->partUser(user) == false){
				c->erase(its);
				delete (*its);
				*its = NULL;
			}
			else {
				(*its)->broadcastChan("PART " + channelName + " " + reason, user);
			}
			return;
		}
	}

	user->reply(ERR_NOSUCHCHANNEL(user->getNickname(), channelName));
}
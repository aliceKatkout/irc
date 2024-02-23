/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabourd <mrabourd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 12:51:49 by mrabourd          #+#    #+#             */
/*   Updated: 2024/02/23 10:36:29 by mrabourd         ###   ########.fr       */
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
	Channel *channel;
	std::string reason;

	if (channelName.empty()){
		user->reply(ERR_NEEDMOREPARAMS(user->getNickname(), "PART"));
	}

	if (args.size() > 2) {
		std::vector<std::string>::iterator it = (args.begin()+2);

		for (; it != args.end(); it++){
			reason = reason + (*it) + " ";
		}
	}

	// Server *s = user->getServer();
	std::vector<Channel *> *c = user->getServer()->getChannels();
	std::vector<Channel *>::iterator its = c->begin();
	// std::vector<Channel *>::iterator it = user->getServer()->getChannels().begin() ;
	
	for (; its != c->end(); its++){
		if ((*its)->getName() == channelName){
			// std::cout << channelName << " has to kick " << user->getNickname() << " from its list" << std::endl;
			channel = (*its);
			user->reply("PART " + channel->getName() + " " + reason);
			// channel->broadcastChan("PART " + channel->getName() + " " + reason, user);
			if (channel->partUser(user) == false){
				delete (*its);
				*its = NULL;
				c->erase(its);
				// c->clear();
				break;
			}
			if ((*channel->getUsers()).size() >= 1){
				// std::cout << "there are " << channel->getUsers().size() << " people in this channel" << std::endl;
				channel->broadcastChan("PART " + channel->getName() + " " + reason, user);
			}
		}
		else if (its == c->end()){ // devrait rentrer la dedans
			user->reply(ERR_NOSUCHCHANNEL(user->getNickname(), channelName));
		}
	}


	// VIRER le channel de la lite des channels dans le user, mais ca fait segfault :
	
	// Channel *toRemove = user->getOneChannel(channelName);
	// std::vector<Channel *> *cha = user->getChannels();
	// std::vector<Channel *>::iterator itc = cha->begin();
	
	// for ( ; itc != cha->end() ; itc++){
	// 	// std::cout << "itc: " << (*itc)->getName() << std::endl;
	// 	if (*itc == channel){
	// 		std::cout << "removing " << (*itc)->getName() << " from list of channels in the user" << std::endl;
	// 		// displayChannels(cha);
	// 		cha->erase(itc);
	// 		std::cout << "Channel erased" << std::endl;
	// 		break ;
	// 	}
	// }

	// if (cha->empty() == true){
	// 	std::cout << "There is no channel left in this server" << std::endl;
	// 	return ;
	// }

	// if (c->empty() == true)
		// std::cout << "There is no channel left in this server" << std::endl;


	// displayChannels(*c);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabourd <mrabourd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 12:51:49 by mrabourd          #+#    #+#             */
/*   Updated: 2024/02/01 15:38:39 by mrabourd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Command.hpp"

/*
-virer le user du channel via le serveur
-si c'etait le dernier user, delete le channel
-virer le channel de la liste des channel dans le user
*/

void PartCmd::execute(User *user, std::vector<std::string> args) {
	
	std::string channelName = *(args.begin()+1);
	std::cout << "channel to get out from: " << channelName << std::endl;
	
	Server *s = user->getServer();
	std::vector<Channel *> c = s->getChannel();
	std::vector<Channel *>::iterator its = c.begin();
	// std::vector<Channel *>::iterator it = user->getServer()->getChannel().begin() ;

	for (; its != c.end(); its++){
		if ((*its)->getName() == channelName){
			std::cout << channelName << " has to kick " << user->getNickname() << " from its list" << std::endl;
			if ((*its)->kickUser(user) == false){
				c.erase(its);
				std::cout << "Channel " << channelName << " deleted successfully " << std::endl;
				break;
			}
		}
	}

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
	
	if (args.size() > 0) {
		std::vector<std::string>::iterator it = (args.begin()+2);

		for (; it != args.end(); it++){
			reason = reason + (*it) + " ";
		}
	}
	user->reply("PART " + *(args.begin()+1) + " " + reason);
}
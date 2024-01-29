/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabourd <mrabourd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 18:36:49 by mrabourd          #+#    #+#             */
/*   Updated: 2024/01/29 19:12:32 by mrabourd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Command.hpp"


static int ChannelExistsAlready(User *user, std::string name) {
	Server *s = user->getServer();
	std::vector<Channel *> c = s->getChannel();
	std::vector<Channel *>::iterator it_s = c.begin();
	// std::vector<Channel *>::iterator it_s = user->getServer()->getChannel().begin() ;

	std::cout << "looking for channel with " << name << " as name in server" << std::endl;
	for (; it_s != c.end(); it_s++){
		if ((*it_s)->getName() == name){
			return (1);
		}
    }
	return (0);
}

void JoinCmd::execute(User *user, std::vector<std::string> args){
	std::cout << "enter join command !!! " << std::endl;
    
	// if (args.size() == 1)
	// {
	// 	std::cerr << "There is an argument missing" << std::endl;
	// 	return ;
	// }
	if (ChannelExistsAlready(user, args.back()) == 1){
		std::cout << "Channel found!" << std::endl;
	}
	
    std::cout << "name of channel should be: " << *(args.begin()) << std::endl;
	std::string channelName = *(args.begin());
    std::string password = "";
    if (args.size() > 2){
        password = *(args.begin() + 2);
    }
    
    user->getServer()->createChannel(channelName);
	// Channel *newChannel = new Channel(channelName, NULL);
	user->getChannel().push_back(user->getServer()->getChannel().back());	
		
	user->reply("332 " + user->getChannel().back()->getName() + " :topic ");
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabourd <mrabourd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 18:36:49 by mrabourd          #+#    #+#             */
/*   Updated: 2024/02/02 14:37:36 by mrabourd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Command.hpp"


static Channel * ChannelExistsAlready(User *user, std::string name) {
	Server *s = user->getServer();
	std::vector<Channel *> c = s->getChannel();
	std::vector<Channel *>::iterator it_s = c.begin();
	// std::vector<Channel *>::iterator it_s = user->getServer()->getChannel().begin() ;

	for (; it_s != c.end(); it_s++){
		if ((*it_s)->getName() == name){
			std::cout << "looking for channel with " << name << " as name in server" << std::endl;
			return (*it_s);
		}
    }
	return (NULL);
}

void JoinCmd::execute(User *user, std::vector<std::string> args){
    
    std::cout << "name of channel should be: " << *(args.begin() + 1) << std::endl;
	std::string channelName = *(args.begin() + 1);

	std::cout << "channel name joined: " << channelName << std::endl;
	
	// if (args.size() == 1)
	// {
	// 	std::cerr << "There is an argument missing" << std::endl;
	// 	return ;
	// }
	
    // std::string password = "";
    // if (args.size() > 2){
    //     password = *(args.begin() + 2);
    // }
    Channel *newChannel = NULL;
	if (ChannelExistsAlready(user, args.back()) != NULL){
		std::cout << "Channel found!" << std::endl;
		newChannel = ChannelExistsAlready(user, args.back());
	}
	else {
		std::cout << "Channel not found. Creating new channel..." << std::endl;
		newChannel = user->getServer()->createChannel(channelName, user);
	}
	newChannel->addUser(user);
	user->addChannel(newChannel);

	std::cout << "There are " << user->getChannel().size() << " channels for this user" << std::endl;
	std::cout << "There are " << newChannel->getUsers().size() << " users in this channel" << std::endl;

	user->reply("JOIN " + *(args.begin()+1));
	user->reply("332 " + *(args.begin()+1) + newChannel->getTopic());

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

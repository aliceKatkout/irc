/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 17:16:46 by mrabourd          #+#    #+#             */
/*   Updated: 2024/02/20 17:24:58 by avedrenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Command.hpp"

void QuitCmd::execute(User *user, std::vector<std::string> args) {
    Server *server = user->getServer();

    std::string reason = "";

    if (args.size() > 1) {
		std::vector<std::string>::iterator it = (args.begin()+1);

		for (; it != args.end(); it++){
			reason = reason + (*it) + " ";
		}
	}

    // Channel *chan;

    // si user is in a channel, delete the user from the channel(s)
    // if (user->getChannel()->size() > 0){
	// 	std::vector<Channel *> *channel = user->getChannel();
	// 	std::vector<Channel *>::iterator it_c = channel->begin();

	// 	for ( ; it_c != channel->end(); ++it_c) {
	// 		std::cout << (*it_c)->getName() << std::endl;
	// 		(*it_c)->removeUser(user);
	// 	}
    // }


	if (reason.size() <= 0)
		reason = "";


    user->reply("QUIT :" + reason + "\r\n");

	//c'est de la merde

	/* std::map<int, User *> connectedUsers = server->getConnectedUsers();
	if (server->getConnectedUsers().size() == 0)
		return ;
	for (std::map<int, User *>::iterator it = connectedUsers.begin(); it != connectedUsers.end(); it++) {
		if (it->second->getFd() != user->getFd())
       		it->second->reply("QUIT :" + reason);
    } */
	server->UserDisconnect(user->getFd());

}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabourd <mrabourd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 17:16:46 by mrabourd          #+#    #+#             */
/*   Updated: 2024/02/20 18:47:41 by mrabourd         ###   ########.fr       */
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
	std::cout << "connected users nb: " << server->getConnectedUsers()->size() << std::endl;

	if (server->getConnectedUsers()->size() == 0)
		return ;

	std::cout << "reason: " << reason << std::endl;

	if (reason != ""){
		broadcastQuit(reason, user);
	}
	
	server->UserDisconnect(user->getFd());
}

void	QuitCmd::broadcastQuit(std::string message, User *user){
	Server *server = user->getServer();
	std::map<int, User *> *connectedUsers = server->getConnectedUsers();
	std::map<int, User *>::iterator it = connectedUsers->begin();

	std::cout << "size of connected users: " << (*connectedUsers).size() << std::endl;
	// RECUPERE LE MAUVAIS NOMBRE DE USERS DANS LE SERVEUR, ENCORE UN PROBLEME DE POINTEURS ?
	
	for ( ; it != connectedUsers->end(); it++) {
	
		if (it->first != user->getFd()){
			it->second->reply("QUIT " + message);
		}
	}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabourd <mrabourd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 17:16:46 by mrabourd          #+#    #+#             */
/*   Updated: 2024/02/15 18:16:53 by mrabourd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Command.hpp"

void QuitCmd::execute(User *user, std::vector<std::string> args) {
    // Server *server = user->getServer();

    std::string reason = args.empty() ? "leaving" : args.at(1);
    std::cout << "Reason at(0): " << reason << std::endl;

	reason.at(0) == ':' ? reason.substr(1) : reason;
    std::cout << "Reason is: " << reason << std::endl;

    // if (args.size() > 1) {
	// 	std::vector<std::string>::iterator it = (args.begin()+1);

	// 	for (; it != args.end(); it++){
	// 		reason = reason + (*it) + " ";
	// 	}
	// }

    // ADD: si user is in a channel, delete the user from the channel

    // Channel *chan;

    if (user->getChannel().size() > 0){
		std::vector<Channel *>::iterator it;
		for (it = user->getChannel().begin() ; it != user->getChannel().end(); it++){
			(*it)->removeUser(user);
		}
    }

	if (reason.size() <= 0)
		reason = "";

    user->reply("QUIT :" + reason);
    
    // server->UserDisconnect(user->getFd());

	// std::map<int, User *> connectedUsers = server->getConnectedUsers();
	// for (std::map<int, User *>::iterator it = connectedUsers.begin(); it != connectedUsers.end(); it++) {
    //     it->second->reply("QUIT :" + reason);
    // }

}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabourd <mrabourd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 17:16:46 by mrabourd          #+#    #+#             */
/*   Updated: 2024/02/15 14:02:18 by mrabourd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Command.hpp"

void QuitCmd::execute(User *user, std::vector<std::string> args) {
    Server *server = user->getServer();

    std::string reason;

    if (args.size() > 1) {
		std::vector<std::string>::iterator it = (args.begin()+1);

		for (; it != args.end(); it++){
			reason = reason + (*it) + " ";
		}
	}
    // std::cout << "Reason is: " << reason << std::endl;

    user->reply("QUIT :" + reason);
    
    server->UserDisconnect(user->getFd());

	// std::map<int, User *> connectedUsers = server->getConnectedUsers();
	// for (std::map<int, User *>::iterator it = connectedUsers.begin(); it != connectedUsers.end(); it++) {
    //     it->second->reply("QUIT :" + reason);
    // }

}
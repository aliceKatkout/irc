/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 17:16:46 by mrabourd          #+#    #+#             */
/*   Updated: 2024/02/21 12:38:44 by avedrenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Command.hpp"

void QuitCmd::execute(User *user, std::vector<std::string> args) {
   // Server *server = user->getServer();

    std::string reason = "";

    if (args.size() > 1) {
		std::vector<std::string>::iterator it = (args.begin()+1);

		for (; it != args.end(); it++){
			reason = reason + (*it) + " ";
		}
	}

    user->reply("QUIT :" + reason);


	//server->UserDisconnect(user->getFd());
}

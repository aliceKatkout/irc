/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UserCmd.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabourd <mrabourd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 14:54:02 by avedrenn          #+#    #+#             */
/*   Updated: 2024/02/15 18:00:26 by mrabourd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Command.hpp"

void UserCmd::execute(User *user, std::vector<std::string> args) {
	if (args.size() > 3) {
		user->setUsername(args[1]);

		std::string realname;
		
		std::vector<std::string>::iterator it = args.begin()+3;

		for ( ; it != args.end(); it++){
			realname += (*it) + " ";
		}
		user->setRealname(realname);
		//user->setHostname(args[1]);
		user->reply("💯 Username set to " + user->getUsername());
		user->welcome();
	}
	else {
		// send error
	}
}
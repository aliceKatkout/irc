/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UserCmd.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 14:54:02 by avedrenn          #+#    #+#             */
/*   Updated: 2024/01/29 13:47:30 by avedrenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Command.hpp"

void UserCmd::execute(User *user, std::vector<std::string> args) {
	if (args.size() > 3) {
		user->setUsername(args[0]);
		user->setRealname(args[2]);
		//user->setHostname(args[1]);
		user->reply("002 " + user->getPrefix() + ": Username set to " + user->getUsername());
	}
	else {
		// send error
	}
}
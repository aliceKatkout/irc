/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UserCmd.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 14:54:02 by avedrenn          #+#    #+#             */
/*   Updated: 2024/02/07 10:31:52 by avedrenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Command.hpp"

void UserCmd::execute(User *user, std::vector<std::string> args) {
	if (args.size() > 3) {
		user->setUsername(args[1]);
		user->setRealname(args[3]);
		//user->setHostname(args[1]);
		user->reply("💯 Username set to " + user->getUsername());
		user->welcome();
	}
	else {
		// send error
	}
}
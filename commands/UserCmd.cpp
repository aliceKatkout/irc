/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UserCmd.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 14:54:02 by avedrenn          #+#    #+#             */
/*   Updated: 2024/01/25 14:54:14 by avedrenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Command.hpp"

void UserCmd::execute(User *user, std::vector<std::string> args) {
	if (args.size() == 1) {
		user->setUsername(args[0]);
	}
	else {
		// send error
	}
}
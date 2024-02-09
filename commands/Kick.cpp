/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 14:04:16 by avedrenn          #+#    #+#             */
/*   Updated: 2024/02/09 15:14:35 by avedrenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Command.hpp"

void KickCmd::execute(User *user, std::vector<std::string> args) {
	(void)user;
	(void)args;
	if (args.size() > 2) {
	 //user->kick(args[1], args[2]);
	}
	else {

	}
}

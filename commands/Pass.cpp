/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 14:53:18 by avedrenn          #+#    #+#             */
/*   Updated: 2024/01/29 15:06:39 by avedrenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/Command.hpp"

void PassCmd::execute(User *user, std::vector<std::string> args) {
	if (user->getServer()->checkPassword(args[0])) {
		user->setGoodPass(true);
		user->setState(LOGIN);
	}
	else {
		user->setGoodPass(false);
		user->reply("464 :Password incorrect");
		user->setState(DISCONNECTED);
	}
}
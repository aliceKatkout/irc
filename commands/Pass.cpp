/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 14:53:18 by avedrenn          #+#    #+#             */
/*   Updated: 2024/01/29 17:20:21 by avedrenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/Command.hpp"

void PassCmd::execute(User *user, std::vector<std::string> args) {
	std::cout << "PassCmd: " << args[0] << std::endl;
	if (user->getServer()->checkPassword(args[0])){
		user->setGoodPass(true);
		user->reply("000 :Good password");
		user->setState(LOGIN);
	}
	else {
		user->setGoodPass(false);
		user->reply("464 PASS :Password incorrect");
		user->setState(DISCONNECTED);
	}
}
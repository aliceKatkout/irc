/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 14:53:18 by avedrenn          #+#    #+#             */
/*   Updated: 2024/01/30 14:59:08 by avedrenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/Command.hpp"

void PassCmd::execute(User *user, std::vector<std::string> args) {
	std::cout << "PassCmd: " << args[1] << std::endl;
	if (user->getServer()->checkPassword(args[1])){
		user->setGoodPass(true);
		user->reply("000 PASS :Good password");
		user->setState(LOGIN);
	}
	else {
		user->setGoodPass(false);
		user->reply("464 PASS :Password incorrect");
		user->setState(DISCONNECTED);
	}
}
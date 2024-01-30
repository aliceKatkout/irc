/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 14:23:18 by avedrenn          #+#    #+#             */
/*   Updated: 2024/01/30 14:34:50 by avedrenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Command.hpp"

void NickCmd::execute(User *user, std::vector<std::string> args) {
	std::string nickname;

	nickname = args[0][args[0].size() - 1] == '\r' ? args[0].substr(0, args[0].size() - 1) : args[0];
	user->setNickname(nickname);
	std::cout << "Nickname set to " << user->getNickname() << std::endl;

	user->reply("002 " + user->getPrefix() + ": Nickname set to " + user->getNickname());
}
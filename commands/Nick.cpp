/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 14:23:18 by avedrenn          #+#    #+#             */
/*   Updated: 2024/01/30 16:47:48 by avedrenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Command.hpp"

void NickCmd::execute(User *user, std::vector<std::string> args) {
	std::string nickname;

	if (args.size() < 2)
	{
		user->reply("431 :No nickname given");
		return ;
	}
	user->setNickname(args[1]);
	std::cout << "Nickname set to " << user->getNickname() << std::endl;

	user->reply("002 " + user->getPrefix() + ": Nickname set to " + user->getNickname());
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabourd <mrabourd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 14:23:18 by avedrenn          #+#    #+#             */
/*   Updated: 2024/02/01 15:49:04 by mrabourd         ###   ########.fr       */
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

	user->reply("002 " + user->getPrefix() + " Nickname set to " + user->getNickname());
}
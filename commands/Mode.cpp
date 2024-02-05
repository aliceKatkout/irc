/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 18:38:55 by mrabourd          #+#    #+#             */
/*   Updated: 2024/02/05 17:52:38 by avedrenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Command.hpp"

static std::string getChannel(std::vector<std::string> args) {
	std::string channel;


}

void ModeCmd::setUserMode(User *user, std::vector<std::string> args) {
	if (args.size() < 3)
	{
		user->reply("461 MODE :Not enough parameters");
		return ;
	}

	char mode = args[2][1];
	switch (mode) {
		case 'i':
			user->setInvisible(args[2][0] == '+');
			break;
		default:
			user->reply("501 MODE :Unknown MODE flag");
			break;
	}
}

void ModeCmd::execute(User *user, std::vector<std::string> args) {

	if (args.size() < 2)
	{
		user->reply("461 MODE :Not enough parameters");
		return ;
	}
	if (args.size() == 2)
	{
		if (args[1] == user->getNickname())
		{
			setUserMode(user, args);
		}
		else
		{
			// get mode of the channel
		}
	}
	else
	{
		// set mode of the channel
	}


}
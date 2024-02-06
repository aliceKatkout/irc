/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 18:38:55 by mrabourd          #+#    #+#             */
/*   Updated: 2024/02/06 14:22:17 by avedrenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Command.hpp"

static std::string getChannel(std::vector<std::string> args) {
	std::string channel;
	if (args.size() >= 3)
	{
		if (args[1][0] == '#' || args[1][0] == '&')
			channel = args[1];
		else
			channel = args[2];
	}
	return channel;

}

void ModeCmd::setChannelMode(User *user, std::vector<std::string> args) {
	if (args.size() < 3)
	{
		user->reply("461 MODE :Not enough parameters");
		return ;
	}

	std::string channel = getChannel(args);
	if (channel.empty())
	{
		user->reply("461 MODE :Not enough parameters");
		return ;
	}

	Channel *chan = user->getOneChannel(channel);
	if (chan == NULL)
	{
		user->reply("403 " + channel + " :No such channel");
		return ;
	}

	char mode = args[2][1];
	switch (mode) {
		case 'i':
			chan->setInviteOnly(args[2][0] == '+');
			user->reply("MODE " + channel + " " + args[2]);
			break;
		case 't':
			if (args.size() < 4)
			{
				user->reply("461 MODE :Not enough parameters");
				return ;
			}
			chan->setTopic(args[3]);
			user->reply("MODE " + channel + " " + args[2] + " " + args[3]);
			break;
		case 'l':
			if (args.size() < 3)
			{
				user->reply("461 MODE :Not enough parameters");
				return ;
			}
			if (args.size() == 3)
			{
				chan->setLimit(100);
				user->reply("MODE " + channel + " " + args[2] + " Channel limit set to 100 (default)");
			}
			else
			{
				chan->setLimit(atoi(args[3].c_str()));
				user->reply("MODE " + channel + " " + args[2] + " " + args[3]);
			}
			break;
		case 'o':
			chan->setOperator(user, (args[2] == "+o" ? true : false));
			user->reply("MODE " + channel + " " + args[2] );
			break;
		case 'k':
			chan->setPassword(args[3]);
			user->reply("MODE " + channel + " " + args[2] + " " + args[3] + " Channel password set");
			break;
		default:
			user->reply("501 MODE :Unknown MODE flag");
			break;
	}
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
			user->reply("MODE " + user->getNickname() + " " + args[2]);
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
	if (args.size() >= 2)
	{
		if (args[1] == user->getNickname())
			setUserMode(user, args);
		else
			setChannelMode(user, args);

	}



}
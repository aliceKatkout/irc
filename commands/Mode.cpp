/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabourd <mrabourd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 18:38:55 by mrabourd          #+#    #+#             */
/*   Updated: 2024/02/23 10:46:43 by mrabourd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Command.hpp"

static std::string getChannels(std::vector<std::string> args) {
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
	// std::cout << "mode: " << args[1] << std::endl;

	if (args.size() < 3)
		return (user->reply("461 MODE :Not enough parameters"));

	std::string channelName = getChannels(args);
	if (channelName.empty())
		return (user->reply("461 MODE :Not enough parameters"));

	Channel *chan = user->getServer()->findChannelByName(channelName);
	if (chan == NULL)
		return(user->reply("403 " + channelName + " :No such channelName"));

	// std::cout << "args size: " << args.size() << std::endl;


	User *toAdd = args.size() < 4 ? (NULL) : (chan->getUserByNick(args[3]));
	
	if (args[2].size() != 2)
		return (user->reply(ERR_NEEDMOREPARAMS(chan->getName(), "MODE")));

	char mode = args[2][1];
	// std::cout << "mode: " << mode << std::endl;
	switch (mode) {
		case 'i':
		// si le user est un operator il peut set le 'invite only' flag to true
		// sinon : '482 user #channel :You must have channel halfop access or above to set channel mode i'
			if (!chan->isUserOperator(user))
				return (user->reply("482 " + user->getNickname() + " " + chan->getName() +
					" :You must have channel halfop access or above to set channel mode i"));
			chan->setInviteOnly(args[2][0] == '+');
			user->reply("MODE " + channelName + " " + args[2]);
			break;
		case 't':
			if (!chan->isUserOperator(user))
				return (user->reply("482 " + user->getNickname() + " " + chan->getName() + " :You must have channel halfop access or above to set channel mode t"));
			chan->setTopicProtection(args[2][0] == '+');
			user->reply("MODE " + channelName + " " + args[2]);
			break;
		case 'l':
			if (args.size() != 4 && args[2][0] == '+'){
				user->reply(ERR_NEEDMOREPARAMS(chan->getName(), "MODE"));
				return;
			}
			else if (args[2][0] == '+' && (atoi(args[3].c_str()) <= 0 || ((*chan->getUsers()).size() > (size_t)atoi(args[3].c_str())))) {
				return (user->reply("MODE " + channelName + " " + args[2] + " :Wrong parameters"));
			}
			else if (args[2][0] == '-'){
				chan->setLimit(100);
				return (user->reply("MODE " + channelName + " " + args[2] + " :Channel limit is reset to 100"));
			}
			chan->setLimit(atoi(args[3].c_str()));
			user->reply("MODE " + channelName + " " + args[2] + " " + args[3]);
			break;
		case 'o':
			if (args.size() < 4 || args[3].empty())
				return (user->reply("461 MODE :Not enough parameters"));
			if (toAdd == NULL)
				return (user->reply("MODE " + args[3] + " " + channelName + " :They aren't on that channel"));
			if (!chan->isUserOperator(user))
				return (user->reply("MODE " + channelName + " " + args[2] + " :You're not an operator"));

			chan->setOperators(toAdd, (args[2] == "+o" ? true : false));
			user->reply("MODE " + chan->getName() + " " + args[2] + " :" + toAdd->getNickname());
			chan->broadcastChan("MODE " + chan->getName() + " " + args[2] + " :" + toAdd->getNickname(), user);
			// user->reply("324 " + user->getUsername() + " " + channelName + " :+nt");
			break;
		case 'k':
			chan->setPassword(args[3]);
			user->reply("MODE " + channelName + " " + args[2] + " " + args[3] + " Channel password set");
			break;
		default:
			user->reply("472 " + args[2] + " :is unknown mode char to me");
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
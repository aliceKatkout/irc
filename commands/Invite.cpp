/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabourd <mrabourd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 16:44:04 by mrabourd          #+#    #+#             */
/*   Updated: 2024/02/05 13:16:48 by mrabourd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Command.hpp"

static Channel *channelExists(std::string channelName, User *user) {

	std::vector<Channel *> channel = user->getChannel();
	std::vector<Channel *>::iterator it_c = channel.begin();

	// std::cout << (*it_c)->getName() << std::endl;

	for ( ; it_c != channel.end(); ++it_c) {
		if ((*it_c)->getName() == channelName){
			return (*it_c);
		}
	}
	return (NULL);
}

static bool userIsMemberOfChannel(Channel *channel, User *user){
	
	std::vector<User *> users = channel->getUsers();
	std::vector<User *>::iterator it_u = users.begin();

	for ( ; it_u != users.end(); it_u++) {
		if ((*it_u) == user){
			return (true);
		}
	}
	return (false);
}

void InviteCmd::execute(User *user, std::vector<std::string> args) {
	
	std::string userInvited = *(args.begin()+1);
	std::string channelName = *(args.begin()+2);

	Channel *chann = channelExists(channelName, user);

	if (chann != NULL){
		if (userIsMemberOfChannel(chann, user) == true){
			user->reply("INVITE " + userInvited + " "  + channelName );
			user->reply("431 " + channelName + " " + user->getUsername());
		}		
	}
	
}
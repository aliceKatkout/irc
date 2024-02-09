/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabourd <mrabourd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 16:44:04 by mrabourd          #+#    #+#             */
/*   Updated: 2024/02/09 17:18:25 by mrabourd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Command.hpp"

static Channel *channelExists(std::string channelName, User *user) {

	if (channelName == "")
		return NULL;
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
			
			// if the channel is an invite only channel
			if (channel->getInviteOnly() == true)
			{
				std::cout << "the channel is an invite only" << std::endl;
				if (channel->getOperator() == user){
					std::cout << "the user is the operator" << std::endl;
					return (true);
				}
				else{
					// 473    ERR_INVITEONLYCHAN
					// "<channel> :Cannot join channel (+i)"
					std::cout << "the user is not the operator" << std::endl;
					user->reply("473 " + channel->getName() + " :Cannot join channel (invite only)");
					return (false);
				}
			}
			// if not, anyone can invite
			else{
				// std::cout << "the channel is not an invite only" << std::endl;
				return (true);
			}
		}
	}
	return (false);
}

static User * invitedUser(User *inviting, std::string invited){

	Server *s = inviting->getServer();
	std::map<int, User *> connectedUsers = s->getConnectedUsers();
	for (std::map<int, User *>::iterator it = connectedUsers.begin(); it != connectedUsers.end(); it++) {
		if (it->second->getNickname() == invited)
			return (it->second);
	}

	return (NULL);
}

static bool userIsAlreadyOnChannel(Channel *channel, User *user){
	if (user == NULL)
		return (false);

	std::vector<User *> u = channel->getUsers();
	std::vector<User *>::iterator it = u.begin();

	for ( ; it != u.end() ; it++) {
		if ((*it) == user){
			// if is already on channel : 443 mrabourd bouldeneige #trivia :is already on channel
			return (true);
		}
	}
	return (false);
}

void InviteCmd::execute(User *user, std::vector<std::string> args) {
	
	std::string userInvited = *(args.begin()+1);
	std::string channelName = *(args.begin()+2);

	Channel *chann = channelExists(channelName, user);
	User *invited = invitedUser(user, userInvited);
	
	if (chann != NULL){
		if (userIsMemberOfChannel(chann, user) == true){
			if (userIsAlreadyOnChannel(chann, invited) == true){
				user->reply("443 " + invited->getNickname() + " " + chann->getName() + " :is already on channel");
				return ;
			}
			if (invited != NULL){
				std::cout << "inviting " << invited->getNickname() << std::endl;
				user->reply("INVITE " + invited->getNickname() + " "  + channelName );
				user->reply("341 " + user->getNickname() + " " + userInvited + " :" + chann->getName());
				// user->reply("431 " + channelName + " " + user->getUsername());
				invited->write(":" + user->getPrefix() + " INVITE " + invited->getNickname() + " :"  + chann->getName() );
				chann->setInvitedUsers(userInvited);
				// chann->broadcastChan("INVITE " + invited->getNickname() + " " + channelName, user);
			}
			else {
				user->reply("401 " + user->getNickname() + " " + userInvited + " :No such nick/channel");
			}
		}
	}
	else {
		std::cout << "the channel doesn't exist!" << std::endl;
		return ;
	}
}
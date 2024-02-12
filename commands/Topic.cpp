/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabourd <mrabourd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 18:05:34 by mrabourd          #+#    #+#             */
/*   Updated: 2024/02/12 18:14:59 by mrabourd         ###   ########.fr       */
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

void TopicCmd::execute(User *user, std::vector<std::string> args) {

	// std::cout << "args 1 " << (*args.begin()) <<std::endl;
	std::string channelName = *(args.begin() + 1);
	// if (channelName[0] == '#'){
	// 	std::cout << "remove #" << std::endl;
	// 	channelName = channelName.substr(1, channelName.size() - 1 );
	// 	std::cout << "new name: " << channelName << std::endl;
	// }
	std::string topic;

	if (args.size() > 1) {
		std::vector<std::string>::iterator it = (args.begin() + 2);

		for (; it != args.end(); ++it){
			topic = topic + (*it) + " ";
		}
	}
	if (topic[0] == ':'){
		topic = topic.substr(1, topic.size() - 1);
	}

	Channel *chann = channelExists(channelName, user);
	//(":localhost 332 " + user + " #" + channel +  " :" + topic + "\r\n")

	if (chann != NULL){
		if (topic.empty()){
			// RENTRE JAMAIS LA DEDANS, essaye de print tpic
			if (chann->getTopic() == ""){
				user->reply("331 " + channelName +  " :No topic is set\r\n");
				return ;
			}
			else
				user->reply("TOPIC " + user->getNickname() + "# " + channelName + " :" + chann->getTopic());
		}
		if (chann->isUserOperator(user)){
			/* change topic of channel */
			if (topic != ""){
				chann->setTopic(topic);
				chann->broadcastChan("TOPIC " + channelName + " :" + topic, user);
				user->reply("TOPIC " + channelName + " :" + topic);
				// chann->broadcastChan("332 " + user->getNickname() + " " + channelName + " " + chann->getTopic(), user);
				
			}

		}
		else
		{
			user->reply("482 " + *(args.begin()+1) +  " :You're not channel operator\r\n");
			// break ;
		}
	}
	else
	{
		std::cout << "Channel " << channelName << " doesn't exist!" << std::endl;
	}

	// std::vector<Channel *> channel = user->getChannel();
	// std::vector<Channel *>::iterator it_c = channel.begin();

	// std::cout << (*it_c)->getName() << std::endl;

	// for ( ; it_c != channel.end(); ++it_c) {
	// 	if ((*it_c)->getName() == channelName){
		// 	if ((*it_c)->getOperator() == user){
		// 		/* change topic of channel */
		// 		(*it_c)->setTopic(topic);
		// 		user->reply("TOPIC " + channelName + " " + topic);
		// 		// user->reply("332 " + channelName + " " + topic);

		// 	}
		// 	else
		// 	{
		// 		user->reply("482 " + *(args.begin()+1) +  " :You're not channel operator\r\n");
		// 		break ;
		// 	}

		// }
	}


// When the operator leaves but other clients are in,
// no one becomes operator and no one can change the topic anymore.
// The operator is no more an operator when he comes back in
// so nobody can change the topic, or any mode, anymore at all.

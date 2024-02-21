/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabourd <mrabourd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 18:05:34 by mrabourd          #+#    #+#             */
/*   Updated: 2024/02/21 16:28:58 by mrabourd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Command.hpp"

static Channel *channelExists(std::string channelName, User *user) {

	std::vector<Channel *> *channel = user->getChannel();
	// if (!(channel))
	// 	return (NULL);
	std::vector<Channel *>::iterator it_c = channel->begin();

	// std::cout << (*it_c)->getName() << std::endl;

	for ( ; it_c != channel->end(); it_c++) {
		if ((*it_c)->getName() == channelName){
			return (*it_c);
		}
	}
	return (NULL);
}

void TopicCmd::execute(User *user, std::vector<std::string> args) {

	std::string channelName = *(args.begin() + 1);
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

	if (!chann)
		return (user->reply("403 " + channelName + " :No such channel"));

	if (topic.empty()){
		if (chann->getTopic() == "")
			return (user->reply("331 " + channelName +  " :No topic is set\r\n"));
		else
			return (user->reply("TOPIC " + user->getNickname() + "# " + channelName + " :" + chann->getTopic()));
	}

	if (chann->getTopicProtection() && !chann->isUserOperator(user))
		return (user->reply("482 " + channelName + " :You're not channel operator\r\n"));

	chann->setTopic(topic);
	chann->broadcastChan("TOPIC " + channelName + " :" + topic, user);
	user->reply("TOPIC " + channelName + " :" + topic);
}
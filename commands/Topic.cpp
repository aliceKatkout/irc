/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabourd <mrabourd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 18:05:34 by mrabourd          #+#    #+#             */
/*   Updated: 2024/02/02 14:46:40 by mrabourd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Command.hpp"

void TopicCmd::execute(User *user, std::vector<std::string> args) {
	std::cout << "Enter topic comd" << std::endl;
	std::cout << "arg1:" << *(args.begin()) << std::endl;
	std::cout << "arg2:" << *(args.begin() + 1) << std::endl;

	std::string channelName = *(args.begin()+1);
	std::string topic;
	
	if (args.size() > 1) {
		std::vector<std::string>::iterator it = (args.begin()+2);

		for (; it != args.end(); ++it){
			topic = topic + (*it) + " ";
		}
		std::cout << "topic: " << topic << std::endl;
	}
	else
	{
		user->reply("331 " + channelName +  " :No topic is set\r\n");
		return ;
	}

	std::vector<Channel *> channel = user->getChannel();
	std::vector<Channel *>::iterator it_c = channel.begin();

	std::cout << (*it_c)->getName() << std::endl;

	for ( ; it_c != channel.end(); ++it_c) {
		if ((*it_c)->getName() == channelName){
			if ((*it_c)->getOperator() == user){
				/* change topic of channel */
				// user->reply("332 " + *(args.begin()) + " :" + *(args.begin()+1) + *(args.begin()+2) );
				(*it_c)->setTopic(topic);
				std::cout << "topic st to : " << (*it_c)->getTopic() << std::endl;
				user->reply(user->getPrefix() + " changed the topic of " + channelName + " to " + topic);
				// user->reply("332 " + channelName + " " + topic);
				
			}
			else
			{
				user->reply("482 " + *(args.begin()+1) +  " :You're not channel operator\r\n");
				// ERR_CHANOPRIVSNEEDED(user_id, channel) (": 482 " + user_id + " " + channel + " :You're not channel operator\r\n")
			}
			
		}
	}


// When the operator leaves but other clients are in,
// no one becomes operator and no one can change the topic anymore.
// The operator is no more an operator when he comes back in 
// so nobody can change the topic, or any mode, anymore at all.

}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabourd <mrabourd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 15:13:01 by avedrenn          #+#    #+#             */
/*   Updated: 2024/02/21 15:42:55 by mrabourd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Server.hpp"

std::vector<std::string > split(std::string s, std::string del){
    // Use find function to find 1st position of delimiter.
	std::vector<std::string> res;
    int end = s.find(del);
    while (end != -1) { // Loop until no delimiter is left in the string.
        res.push_back(s.substr(0, end));
        s.erase(s.begin(), s.begin() + end + 1);
        end = s.find(del);
    }
    res.push_back(s.substr(0, end));
	return res;
}

Channel * ChannelExistsAlready(User *user, std::string name) {
	Server *s = user->getServer();
	std::vector<Channel *> *c = s->getChannel();
	std::vector<Channel *>::iterator it_s = c->begin();
	// std::vector<Channel *>::iterator it_s = user->getServer()->getChannel().begin() ;

	for (; it_s != c->end(); it_s++){
		if ((*it_s)->getName() == name){
			// std::cout << "looking for channel with " << name << " as name in server" << std::endl;
			return (*it_s);
		}
    }
	return (NULL);
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabourd <mrabourd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 18:05:34 by mrabourd          #+#    #+#             */
/*   Updated: 2024/01/31 12:36:38 by mrabourd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Command.hpp"

void TopicCmd::execute(User *user, std::vector<std::string> args) {
    std::cout << "Enter topic comd" << std::endl;
    std::cout << "arg1:" << *(args.begin()) << std::endl;
    std::cout << "arg2:" << *(args.begin() + 1) << std::endl;

    // if the user is the operator of the channel
    user->reply("332 " + *(args.begin()) + " :" + *(args.begin()+1) + *(args.begin()+2) );

// When the operator leaves but other clients are in,
// no one becomes operator and no one can change the topic anymore.
// The operator is no more an operator when he comes back in 
// so nobody can change the topic, or any mode, anymore at all.

}
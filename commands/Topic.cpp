/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabourd <mrabourd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 18:05:34 by mrabourd          #+#    #+#             */
/*   Updated: 2024/01/29 19:24:35 by mrabourd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Command.hpp"

void TopicCmd::execute(User *user, std::vector<std::string> args) {
    std::cout << "Enter topic comd" << std::endl;
    std::cout << "arg1:" << *(args.begin()) << std::endl;
    std::cout << "arg2:" << *(args.begin() + 1) << std::endl;

    
    user->reply("332 " + *(args.begin()) + " :" + *(args.begin()) );

}
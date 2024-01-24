/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ping.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabourd <mrabourd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 15:11:53 by mrabourd          #+#    #+#             */
/*   Updated: 2024/01/24 19:01:00 by mrabourd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Command.hpp"

void PingCmd::execute(User *user, std::vector<std::string> args){
    std::string ret;
    ret = "Pong";
    (void)args;

    write(user->getFd(), ret.c_str(), 5);
    // fprintf(user->getFd(), ret);
}

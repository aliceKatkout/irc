/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ping.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabourd <mrabourd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 15:11:53 by mrabourd          #+#    #+#             */
/*   Updated: 2024/01/24 17:02:08 by mrabourd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Command.hpp"

void PingCmd::execute(User *user){
    std::string ret;
    ret = "Pong";

    write(user->getFd(), ret.c_str(), 5);
    // fprintf(user->getFd(), ret);
}

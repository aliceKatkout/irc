/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ExecCmd.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabourd <mrabourd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 15:11:53 by mrabourd          #+#    #+#             */
/*   Updated: 2024/01/24 16:33:21 by mrabourd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"


void PingCmd::execute(User *user){
    std::string ret;
    ret = "Pong";

    write(user->getFd(), ret.c_str(), 5);
    // fprintf(user->getFd(), ret);
}

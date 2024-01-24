/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdHandler.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabourd <mrabourd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 15:52:30 by mrabourd          #+#    #+#             */
/*   Updated: 2024/01/24 16:33:06 by mrabourd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CmdHandler.hpp"

CmdHandler::CmdHandler () {
    _cmdMap["PING"] = new PingCmd();
	// _cmdMap["PONG"] = new PongCmd();
}

CmdHandler::~CmdHandler () {
    
}

void CmdHandler::parsing(std::string msg, User *user) {
    
    std::string cmd;
    cmd = msg.substr(0, msg.find(' '));

    if (cmd.length() > 0){
        if (_cmdMap.find(cmd) != _cmdMap.end()){
            _cmdMap[cmd]->execute(user);
        }
    }
    
    // _cmdMap.find(cmd);
    
}
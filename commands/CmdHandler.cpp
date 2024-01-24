/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdHandler.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabourd <mrabourd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 15:52:30 by mrabourd          #+#    #+#             */
/*   Updated: 2024/01/24 19:01:25 by mrabourd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/CmdHandler.hpp"

CmdHandler::CmdHandler () {
    _cmdMap["PING"] = new PingCmd();
	// _cmdMap["PONG"] = new PongCmd();
}

CmdHandler::~CmdHandler () {
    
}

void CmdHandler::parsing(std::string msg, User *user) {
    
    std::string cmd;
    std::vector<std::string> args;

    /* ARGS A PARSER !! */
    args.push_back("chann");
    
    cmd = msg.substr(0, msg.find(' '));

    if (cmd.length() > 0){
        if (_cmdMap.find(cmd) != _cmdMap.end()){
            _cmdMap[cmd]->execute(user, args);
        }
    }
    
}
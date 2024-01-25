/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdHandler.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 15:52:30 by mrabourd          #+#    #+#             */
/*   Updated: 2024/01/25 15:17:37 by avedrenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/CmdHandler.hpp"
#include "../includes/Server.hpp"

CmdHandler::CmdHandler () {
    _cmdMap["PING"] = new PingCmd();
	_cmdMap["NICK"] = new NickCmd();
	_cmdMap["PASS"] = new PassCmd();
	_cmdMap["USER"] = new UserCmd();

	//_cmdMap["JOIN"] = new JoinCmd();
}

CmdHandler::~CmdHandler () {

}

void CmdHandler::parsing(std::string msg, User *user) {

    std::string cmd;
    std::vector<std::string> args;

	args.push_back(msg.substr(msg.find(' ') + 1, msg.length()));

    cmd = msg.substr(0, msg.find(' '));

    if (cmd.length() > 0){
        if (_cmdMap.find(cmd) != _cmdMap.end()){
			args = split(msg, " ");
            _cmdMap[cmd]->execute(user, args);
        }
    }

}
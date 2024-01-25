/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdHandler.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 15:52:30 by mrabourd          #+#    #+#             */
/*   Updated: 2024/01/25 16:49:25 by avedrenn         ###   ########.fr       */
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

    args = split(msg, "/n");


	for (int i = 0; i < (int) args.size(); i++)
		std::cout << args[i] << std::endl;

    if (cmd.length() > 0){
        if (_cmdMap.find(cmd) != _cmdMap.end()){
            args = split(msg, " ");
            _cmdMap[cmd]->execute(user, args);
        }
    }


}
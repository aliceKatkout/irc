/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdHandler.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 15:52:30 by mrabourd          #+#    #+#             */
/*   Updated: 2024/01/29 17:15:55 by avedrenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/CmdHandler.hpp"
#include "../includes/Server.hpp"

CmdHandler::CmdHandler () {
	std::cout << "CmdHandler constructor" << std::endl;
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

    args = split(msg, " \n");
	if (user->getState() == DISCONNECTED)
		return ;

    while ((int) args.size() > 0){
		cmd = args[0];
		std::cout << "cmd = " << cmd << std::endl;
		args.erase(args.begin());
        if (_cmdMap.find(cmd) != _cmdMap.end()){
			std::cout << "executing cmd " << cmd << "with args " << args[0] << std::endl;
            _cmdMap[cmd]->execute(user, args);
			if (!user->getIsRegistered())
				user->welcome();
			if (user->getState() == DISCONNECTED)
				return ;

		}
		//else
				//user->reply("421 " + cmd + " :Unknown command");
	}
}
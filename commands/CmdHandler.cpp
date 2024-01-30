/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdHandler.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 15:52:30 by mrabourd          #+#    #+#             */
/*   Updated: 2024/01/30 15:42:24 by avedrenn         ###   ########.fr       */
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
	_cmdMap["TOPIC"] = new TopicCmd();


	_cmdMap["JOIN"] = new JoinCmd();
}

CmdHandler::~CmdHandler () {

}

void CmdHandler::parsing(std::string msg, User *user) {

    std::vector<std::string> cmds;
    std::vector<std::string> args;

	cmds = split(msg, "\n");
	for (int i = 0; i < (int)cmds.size(); i++)
			std::cout << "cmds[" << i << "] = " << cmds[i] << std::endl;

	if (user->getState() == DISCONNECTED)
		return ;

    while ((int) cmds.size() > 0){
		args = split(cmds[0], " ");
			for (int i = 0; i < (int)args.size(); i++)
				std::cout << "arg[" << i << "] = " << args[i] << std::endl;
		std::cout << "cmd = " << args[0] << std::endl;
		cmds.erase(cmds.begin());
        if (_cmdMap.find(args[0]) != _cmdMap.end()){
			std::cout << "executing cmd " << args[0] << std::endl;
			for (int i = 0; i < (int)args.size(); i++)
				std::cout << "arg[" << i << "] = " << args[i] << std::endl;

            _cmdMap[args[0]]->execute(user, args);
			if (!user->getIsRegistered())
				user->welcome();
			if (user->getState() == DISCONNECTED)
				return ;
		}

	/* 	else
			user->reply("421 " + args[0] + " :Unknown command"); */
	}
}
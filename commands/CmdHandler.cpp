/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdHandler.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 15:52:30 by mrabourd          #+#    #+#             */
/*   Updated: 2024/02/20 16:18:52 by avedrenn         ###   ########.fr       */
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
	_cmdMap["PART"] = new PartCmd();
	_cmdMap["MODE"] = new ModeCmd();
	_cmdMap["INVITE"] = new InviteCmd();
	_cmdMap["PRIVMSG"] = new PrivMsgCmd();
	_cmdMap["KICK"] = new KickCmd();
	_cmdMap["QUIT"] = new QuitCmd();

}

CmdHandler::~CmdHandler () {

}

void CmdHandler::parsing(std::string msg, User *user) {

    std::vector<std::string> cmds;
    std::vector<std::string> args;
	int nb;

	args.clear();
	cmds = split(msg, "\n");
	std::cout << "parsing : " << cmds[0] << std::endl;
	if (user->getState() == DISCONNECTED)
		return ;

    while ((int) cmds.size() > 0){
		args = split(cmds[0], " ");
		nb = args.size() - 1;
		cmds.erase(cmds.begin());
		args[nb] = args[nb][args[nb].size() - 1] == '\r' ? args[nb].substr(0, args[nb].size() - 1) : args[nb];
        if (_cmdMap.find(args[0]) != _cmdMap.end()){
			std::cout << "executing cmd " << args[0] << std::endl;
            _cmdMap[args[0]]->execute(user, args);
			if (!user->getIsRegistered())
				user->welcome();
			if (user->getState() == DISCONNECTED)
				return ;
		}
		else if (args[nb] == "")
			nb++;
		else if (args[0] != "CAP"){
			user->reply("421 " + args[0] + " :Unknown command");
		}
	}
}
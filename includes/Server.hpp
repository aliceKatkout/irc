/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 14:58:54 by mrabourd          #+#    #+#             */
/*   Updated: 2024/02/14 13:14:21 by avedrenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include "User.hpp"
# include "User.hpp"
# include "CmdHandler.hpp"
# include "Channel.hpp"

# include <errno.h>

# include <iostream>
# include <sys/types.h>
# include <sys/socket.h>
# include <sys/poll.h>
# include <netdb.h>
# include <cstring>
# include <stdlib.h>
# include <unistd.h>
# include <vector>
# include <fcntl.h>
# include <map>
// # include <pairs>
# include <algorithm>


# define MAX_EVENTS 10

class CmdHandler;
class User;
class Channel;

class Server {
	private:
		std::map<int, User *>					_connectedUsers;
		std::vector<struct pollfd>				_userFDs;
		// struct addrinfo	_hints;
		struct sockaddr_in serv_addr;
		int opt;
		socklen_t size;
		char *_str_port;
		char *_str_passwd;
		int _port;
		std::string _passwd;
		int _server_fd;
		std::string _hostname;

		CmdHandler *_handler;

		std::vector<Channel *> _channels;

	public:
		Server();
		Server (char *port, char *passwd);
		~Server();

		bool	setPort (char *port);
		bool	setPasswd (char *passwd);

		std::string getHostname() const;

		int init ();
		void start();
		void UserConnect();
		int UserMessage(int);
		void UserDisconnect(int);

		int find_user_fd(int fd);
		User *findUserNick(std::string nick);

		bool checkPassword(std::string &passwd);

		Channel *	createChannel(std::string, User *);

		std::vector<Channel *> *getChannel();
		Channel *getLastChannel();
		std::map<int, User *> getConnectedUsers();
};

std::vector<std::string> split(std::string s, std::string del);
Channel * ChannelExistsAlready(User *user, std::string name);

#endif
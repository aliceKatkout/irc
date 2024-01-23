/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabourd <mrabourd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 14:58:54 by mrabourd          #+#    #+#             */
/*   Updated: 2024/01/23 15:30:55 by mrabourd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include "User.hpp"

# include <iostream>
# include <sys/types.h>
# include <sys/socket.h>
# include <sys/epoll.h>
# include <netdb.h>
# include <cstring>
# include <stdlib.h>
# include <unistd.h>
# include <vector>
# include <fcntl.h>

# define MAX_EVENTS 10

class Server {
	private:
		std::vector<User *>						connectedUsers;
		std::vector<struct pollfd>				userFDs;
		struct addrinfo	_hints;
		char *_str_port;
		char *_str_passwd;
		int _port;
		std::string _passwd;
		int _server_fd;
		// char *_msg;

	public:
		Server();
		Server (char *port, char *passwd);
		~Server();

		bool	setPort (char *port);
		bool	setPasswd (char *passwd);

		void init ();
		void createEpoll();
		void recv_and_forward_msg(int fd);
		std::vector<std::string > split(std::string &s, std::string delimiter);

		ssize_t Send(const char *data, unsigned int len);
		int Receive(char *buffer, unsigned int len);

};

#endif
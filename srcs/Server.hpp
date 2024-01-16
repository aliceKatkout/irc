/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabourd <mrabourd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 14:58:54 by mrabourd          #+#    #+#             */
/*   Updated: 2024/01/16 16:39:41 by mrabourd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include <iostream>
# include <sys/types.h>
# include <sys/socket.h>
# include <sys/epoll.h>
# include <netdb.h>
# include <cstring>
# include <stdlib.h>
# include <unistd.h>

# define MAX_EVENTS 10

class Server {
	private:
		struct addrinfo	_hints;
		char *_str_port;
		char *_str_passwd;
		int _port;
		std::string _passwd;
		int _socket_fd;

	public:
		Server();
		Server (char *port, char *passwd);
		~Server();

		bool	setPort (char *port);
		bool	setPasswd (char *passwd);

		void init ();
		void createEpoll();

		ssize_t Send(const char *data, unsigned int len);
		int Receive(char *buffer, unsigned int len);

};

#endif
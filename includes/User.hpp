/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 14:13:58 by avedrenn          #+#    #+#             */
/*   Updated: 2024/02/12 16:03:20 by avedrenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USER_HPP
# define USER_HPP

# include <iostream>
# include "Channel.hpp"
# include "Server.hpp"

class Server;

enum UserState {
	HANDSHAKE,
	LOGIN,
	ACTIVE,
	DISCONNECTED
};

class User {
	public :
		User(int fd, Server *server);
		~User();
		bool operator==(const User &rhs) const;

		std::string getPrefix() const;
		void write(const std::string &message) const;
		void reply(const std::string &reply);

		int getFd() const;
		std::string getNickname() const;
		std::string getUsername() const;
		bool getGoodPass() const;
		bool getIsRegistered() const;
		Server *getServer() const;
		std::vector<Channel *> getChannel() ;
		Channel *getOneChannel(std::string name);

		void setNickname(std::string nickname);
		void setUsername(std::string username);
		void setRealname(std::string realname);
		void setGoodPass(bool good_pass);
		void setIsRegistered(bool is_registered);
		UserState getState() const;
		UserState findState();
		void setState(UserState state);
		void	welcome();
		void setInvisible(bool invisible);

		User *getUserByNick(std::string nickname);

		void addChannel(Channel *);

	private :
		int _fd;
		std::string _nickname;
		std::string _username;
		std::string _realname;
		std::string _hostname;
		bool 	_is_registered;
		bool 	_good_pass;
		bool 	_invisible;

		Server *_server;

		UserState _state;

		std::vector<Channel *> _channels; // les channels sur lesquels le users est connecte

		/* ajouter a combien de channel le user a le droit de se connecter */

};

#endif
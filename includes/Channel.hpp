/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 18:21:01 by mrabourd          #+#    #+#             */
/*   Updated: 2024/02/13 13:52:40 by avedrenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP

# define CHANNEL_HPP

# include <iostream>
# include <map>
# include <vector>
# include <algorithm>
# include "User.hpp"
# include <csignal>

class User;

class Channel {
	private:
		std::string 			_name;

		std::vector<User *> 	_operators;
		std::vector<User *> 	_joinedUsers;

		bool 		_i; // Set/remove Invite-only channel. true = yes, false = no
		std::string _k; // Définir/supprimer la clé du canal (mot de passe)
		size_t 		_l; //definir / supprimer la limite d'users du chann


		std::string _topic;
		std::vector<std::string> _invitedUsers;
		/* ajouter le nb de users que le chann accepte */

	public:
		Channel(std::string, std::string);
		~Channel();

		void    setOperators(User *, bool);
		void    setLimit(size_t);
		void    setInviteOnly(bool);
		void	setTopic(std::string);
		void	setName(std::string);
		void	setPassword(std::string);
		void	setInvitedUsers(std::string);


		std::string getName() const;
		std::string getPassword() const;
		size_t    	getLimit() const;
		bool 		getInviteOnly() const;
		std::vector<User *> getUsers() ;
		User	*getUserByNick(std::string);
		std::vector<User *>		getOperators();
		bool	isUserOperator(User *);
		std::string getTopic();
		std::vector<std::string> getInvitedUsers();


		bool    addUser(User *, std::string);
		void   	removeUser(User *);
		bool    partUser(User *);

		void	broadcastChan(std::string, User *); // (msg, user)

		bool	topicSet;

		// void	sendMsg()

		// void introduce();
};

#endif
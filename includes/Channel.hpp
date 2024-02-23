/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 18:21:01 by mrabourd          #+#    #+#             */
/*   Updated: 2024/02/23 14:04:00 by avedrenn         ###   ########.fr       */
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
		std::vector<User *> 	*_joinedUsers;

		bool 		_i; // Set/remove Invite-only channel. true = yes, false = no
		std::string _k; // Définir/supprimer la clé du canal (mot de passe)
		int		_l; //definir / supprimer la limite d'users du chann
		bool 		_t; // Set/remove topic protection. true = yes, false = no

		int		_nbUsers;


		std::string _topic;
		std::vector<std::string> _invitedUsers;
		/* ajouter le nb de users que le chann accepte */

	public:
		Channel(std::string, std::string);
		~Channel();

		void    setOperators(User *, bool);
		void    setLimit(int);
		void    setInviteOnly(bool);
		void	setTopic(std::string);
		void	setName(std::string);
		void	setPassword(std::string);
		void	setInvitedUsers(std::string);
		void	setTopicProtection(bool);
		void   	setNbUsers(int);

		bool			getTopicProtection() const;
		std::string 	getName() const;
		std::string 	getPassword() const;
		int    			getLimit() const;
		int				getNbUsers() const;
		bool 			getInviteOnly() const;
		User			*getUserByNick(std::string);
		bool			isUserOperator(User *);
		std::string 	getTopic();
		std::vector<User *> *getUsers() ;
		std::vector<User *>		*getOperators();
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
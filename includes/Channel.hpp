/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabourd <mrabourd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 18:21:01 by mrabourd          #+#    #+#             */
/*   Updated: 2024/01/25 17:52:56 by mrabourd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP

# define CHANNEL_HPP

# include <iostream>
# include <map>
# include <vector>
# include <algorithm>
# include "User.hpp"

class User;

class Channel {
	private:
		std::string _name;

		User * _operator;
		std::vector<User *> _joinedUsers;

		bool _i; // Set/remove Invite-only channel
		std::string _k; // Définir/supprimer la clé du canal (mot de passe)
		size_t _l; //definir / supprimer la limite d'users du chann

		/* ajouter le nb de users que le chann accepte */

	public:
		Channel(std::string, std::string);
		~Channel();
		
		void    setOperator(User *);
		void    setLimit(size_t);
		void    setInviteOnly(bool);

		std::string getName() const;
		std::string getPassword() const;
		size_t    getLimit() const;
		bool getInviteOnly() const;
		
		bool    addUser(User *);
		bool    kickUser(User *);
		// void	sendMsg()
};

#endif
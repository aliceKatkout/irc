/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 14:13:58 by avedrenn          #+#    #+#             */
/*   Updated: 2024/01/25 14:24:42 by avedrenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USER_HPP
# define USER_HPP

# include <iostream>

class User {
	public :
		User(int fd);
		~User();

		int getFd() const;
		std::string getNickname() const;
		std::string getUsername() const;
		bool getGoodPass() const;

		void setNickname(std::string nickname);
		void setUsername(std::string username);
		void setGoodPass(bool good_pass);

	private :
		int _fd;
		std::string _nickname;
		std::string _username;
		bool 	_good_pass;

		/* ajouter a combien de channel le user a le droit de se connecter */

};

#endif
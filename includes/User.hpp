/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabourd <mrabourd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 14:13:58 by avedrenn          #+#    #+#             */
/*   Updated: 2024/01/24 18:58:36 by mrabourd         ###   ########.fr       */
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

	private :
		int _fd;
		std::string _nickname;

		/* ajouter a combien de channel le user a le droit de se connecter */

};

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabourd <mrabourd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 14:13:58 by avedrenn          #+#    #+#             */
/*   Updated: 2024/01/23 18:24:44 by mrabourd         ###   ########.fr       */
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
		// std::string _username;

		// std::string _msg;

};

#endif
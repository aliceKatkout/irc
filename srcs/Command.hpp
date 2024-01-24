/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabourd <mrabourd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:25:49 by mrabourd          #+#    #+#             */
/*   Updated: 2024/01/24 16:19:45 by mrabourd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_HPP

# define COMMAND_HPP

#include <iostream>
#include "User.hpp"
#include <stdio.h>
#include <unistd.h>

class Command {
	private:
		std::string _name;

	public:
		Command();
		virtual ~Command ();

		virtual void execute(User *)  = 0;
};

class PingCmd : public Command {
	private:
		std::string _name;

	public:
		PingCmd(): _name("PING") {}
		~PingCmd () {}

		void execute(User *) ;
};


// class PongCmd : public Command {
// 	private:
// 		std::string _name;

// 	public:
// 		PongCmd(): _name("PONG") {}
// 		~PongCmd () {}

// 		bool execute(User *) ;
// };

#endif
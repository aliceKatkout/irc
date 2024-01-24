/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabourd <mrabourd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:25:49 by mrabourd          #+#    #+#             */
/*   Updated: 2024/01/24 16:57:35 by mrabourd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_HPP

# define COMMAND_HPP

#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include "User.hpp"

class Command {
	private:

	public:
		Command();
		virtual ~Command ();

		virtual void execute(User *)  = 0;
};

class PingCmd : public Command {
	private:

	public:
		PingCmd(){}
		~PingCmd () {}

		void execute(User *) ;
};



#endif
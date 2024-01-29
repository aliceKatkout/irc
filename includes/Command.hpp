/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabourd <mrabourd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:25:49 by mrabourd          #+#    #+#             */
/*   Updated: 2024/01/29 18:09:18 by mrabourd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_HPP

# define COMMAND_HPP

#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <vector>
#include "User.hpp"

class User;

class Command {
	private:

	public:
		Command();
		virtual ~Command ();

		virtual void execute(User *, std::vector<std::string> args)  = 0;
};

class PingCmd : public Command {
	private:

	public:
		PingCmd(){}
		~PingCmd () {}

		void execute(User *, std::vector<std::string> args) ;
};

class NickCmd : public Command {
	private:

	public:
		NickCmd(){}
		~NickCmd () {}

		void execute(User *, std::vector<std::string> args) ;
};

class PassCmd : public Command {
	private:

	public:
		PassCmd(){}
		~PassCmd () {}

		void execute(User *, std::vector<std::string> args) ;
};

class UserCmd : public Command {
	private:

	public:
		UserCmd(){}
		~UserCmd () {}

		void execute(User *, std::vector<std::string> args) ;
};

class Join : public Command {
	private:

	public:
		Join(){}
		~Join () {}

		void execute(User *, std::vector<std::string> args) ;
};

// class Invite : public Command {
// 	private:

// 	public:
// 		Invite(){}
// 		~Invite () {}

// 		void execute(User *, std::vector<std::string> args) ;
// };

class Topic : public Command {
	private:

	public:
		Topic(){}
		~Topic () {}

		void execute(User *, std::vector<std::string> args) ;
};

#endif
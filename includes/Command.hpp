/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:25:49 by mrabourd          #+#    #+#             */
/*   Updated: 2024/02/05 17:46:36 by avedrenn         ###   ########.fr       */
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

class JoinCmd : public Command {
	private:

	public:
		JoinCmd(){}
		~JoinCmd () {}

		void execute(User *, std::vector<std::string> args) ;
};

class InviteCmd : public Command {
	private:

	public:
		InviteCmd(){}
		~InviteCmd () {}

		void execute(User *, std::vector<std::string> args) ;
};

class TopicCmd : public Command {
	private:

	public:
		TopicCmd(){}
		~TopicCmd () {}

		void execute(User *, std::vector<std::string> args) ;
};

class ModeCmd : public Command {
	private:

	public:
		ModeCmd(){}
		~ModeCmd () {}

		void execute(User *, std::vector<std::string> args) ;
		void setUserMode(User *, std::vector<std::string> args);
		void setChannelMode(User *, std::vector<std::string> args);
};

class PartCmd : public Command {
	private:

	public:
		PartCmd(){}
		~PartCmd () {}

		void execute(User *, std::vector<std::string> args) ;
};

#endif
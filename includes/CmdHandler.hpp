/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdHandler.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabourd <mrabourd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 15:51:10 by mrabourd          #+#    #+#             */
/*   Updated: 2024/02/22 15:43:35 by mrabourd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMDHANDLER_HPP

# define CMDHANDLER_HPP

# include <map>
# include "Command.hpp"
# include <iostream>

# define ERR_NEEDMOREPARAMS(user, command) "461 " + user + " " + command + " :Wrong number of parameters"
# define ERR_NOSUCHCHANNEL(user, command) "403 " + user + " " + command + " :No such channel"

class Command;

class CmdHandler {
    private:
        std::map<std::string, Command *> _cmdMap;

    public:
        CmdHandler ();
        ~CmdHandler( );

        int parsing(std::string, User *);
};

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdHandler.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 15:51:10 by mrabourd          #+#    #+#             */
/*   Updated: 2024/01/26 12:44:32 by avedrenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMDHANDLER_HPP

# define CMDHANDLER_HPP

# include <map>
# include "Command.hpp"
# include <iostream>

class Command;

class CmdHandler {
    private:
        std::map<std::string, Command *> _cmdMap;

    public:
        CmdHandler ();
        ~CmdHandler();

        void parsing(std::string, User *);
};

#endif
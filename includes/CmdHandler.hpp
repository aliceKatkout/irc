/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdHandler.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabourd <mrabourd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 15:51:10 by mrabourd          #+#    #+#             */
/*   Updated: 2024/01/24 16:14:11 by mrabourd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMDHANDLER_HPP

# define CMDHANDLER_HPP

# include <map>
# include "Command.hpp"
# include <iostream>


class CmdHandler {
    private:
        std::map<std::string, Command *> _cmdMap;

    public:
        CmdHandler ();
        ~CmdHandler();
        
        void parsing(std::string, User *);
};

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabourd <mrabourd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 18:21:01 by mrabourd          #+#    #+#             */
/*   Updated: 2024/01/24 18:57:05 by mrabourd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP

# define CHANNEL_HPP

# include <iostream>

class Channel {
    private:
        std::string _name;
        std::string _password;

        /* ajouter le nb de users que le chann accepte */

    public:
        Channel(std::string, std::string);
        ~Channel();

        std::string getName() const;
};

#endif
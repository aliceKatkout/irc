/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabourd <mrabourd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 18:36:49 by mrabourd          #+#    #+#             */
/*   Updated: 2024/01/24 19:01:53 by mrabourd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Command.hpp"

void Join::execute(User *user, std::vector<std::string> args){

    (void)user;
    (void)args;
// CmdHandler::parsing -> a faire
    
    /*
    Si channel existe deja : 
        -si ne depasse pas la taille limit de users
         && le user n'est pas banned du channel
         && user a le droit de join (check les 'modes')
            -> server envoie msg aux autres users du channel avec prefix
            -> et envoie msg au user qui a joined
            -> envoie un 'MODE' msg avec les odes du chann
            -> si topic, evoie RPL_TOPIC et RPL_TOPICTIME numerics
            -> envoie RPL_NAMREPLY

        


    Si n'existe pas :
        creer channel, avec ou sans password 
    */
}

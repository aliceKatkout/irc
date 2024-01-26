/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ping.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 15:11:53 by mrabourd          #+#    #+#             */
/*   Updated: 2024/01/26 14:17:03 by avedrenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Command.hpp"

/* 4.6.2 Message PING
Commande: PING
Paramètres: <serveur1> [<serveur2>]

Le message PING est utilisé pour tester la présence d'un client actif à l'autre bout de la connexion. Un message PING est envoyé régulièrement si aucune activité n'est détectée sur une connexion. Si la connexion ne répond pas à la commande PING dans un certain délai, la connexion est fermée.

Tout client qui reçoit un message PING doit répondre au <serveur1> (serveur qui a envoyé le message PING) aussi rapidement que possible, avec un message PONG approprié pour indiquer qu'il est toujours là et actif. Les serveurs ne doivent pas répondre aux commandes PING, mais se fier au PING dans l'autre sens pour indiquer que la connexion est toujours active. Si le paramètre <serveur2> est spécifié, le message PING lui est transmis.

Réponses numériques :

           ERR_NOORIGIN                    ERR_NOSUCHSERVER
Exemples:

PING tolsun.oulu.fi ; serveur envoyant un message PING à un autre serveur pour indiquer qu'il est toujours actif.
PING WiZ ; message PING envoyé au pseudo WiZ
4.6.3 Message PONG
Commande: PONG
Paramètres: <démon> [<démon2>]

Le message PONG est la réponse à un message PING. Si le paramètre <démon2> est donné, le message doit être transmis au démon donné. Le paramètre <démon> est le nom du démon responsable du message PING généré.

Réponses numériques :

           ERR_NOORIGIN                    ERR_NOSUCHSERVER
Exemples:

PONG csd.bu.edu tolsun.oulu.fi ; message PONG de csd.bu.edu à tolsun.oulu.fi */

void PingCmd::execute(User *user, std::vector<std::string> args){
    std::string ret;
	std::cout << "args[0]" << args[0] << std::endl;

	ret = "PONG" + args[0] + ": Pong from " + user->getNickname() + "\r\n";

	write(user->getFd(), ret.c_str(), ret.length());
    // fprintf(user->getFd(), ret);
}

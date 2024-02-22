/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabourd <mrabourd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 15:09:09 by mrabourd          #+#    #+#             */
/*   Updated: 2024/02/22 16:30:21 by mrabourd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/Server.hpp"

void sigint_handler(int signum) {
	std::cout << "Caught signal " << signum << std::endl;
	if (signum == SIGINT)
		g_isRunning = false;
	return ;
}

int main(int ac, char **av) {
	if (ac != 3){
		std::cout << "Invalid number of arguments! ADIOS" << std::endl;
		return (1);
	}

	signal(SIGTERM, SIG_IGN);
	Server server(av[1], av[2]);
	server.init();
	signal(SIGINT, (sighandler_t)sigint_handler);
	server.start();
}
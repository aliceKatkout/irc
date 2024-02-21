/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 15:09:09 by mrabourd          #+#    #+#             */
/*   Updated: 2024/02/21 13:54:18 by avedrenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/Server.hpp"

void sigint_handler(int signum) {
	std::cout << "Caught signal " << signum << std::endl;
	g_isRunning = false;
	return ;
}

int main(int ac, char **av) {
	if (ac != 3){
		std::cout << "Invalid number of arguments! ADIOS" << std::endl;
		return (1);
	}

	Server server(av[1], av[2]);
	server.init();
	signal(SIGINT, (sighandler_t)sigint_handler);
	server.start();
}
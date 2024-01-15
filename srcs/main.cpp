/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabourd <mrabourd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 15:09:09 by mrabourd          #+#    #+#             */
/*   Updated: 2024/01/15 16:15:58 by mrabourd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

int main(int ac, char **av) {
	if (ac != 3){
		std::cout << "Invalid number of arguments! ADIOS" << std::endl;
		return (1);
	}

	Server server(av[1], av[2]);
	server.init();
}
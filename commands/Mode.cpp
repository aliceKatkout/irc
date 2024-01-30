/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabourd <mrabourd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 18:38:55 by mrabourd          #+#    #+#             */
/*   Updated: 2024/01/30 18:59:55 by mrabourd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Command.hpp"

static std::string getChannel(std::vector<std::string> args) {
	
}

void ModeCmd::execute(User *user, std::vector<std::string> args) {

	std::string channel = getChannel(args);
	// std::string param = getParam(args);
	
	
}
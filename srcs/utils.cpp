/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 15:13:01 by avedrenn          #+#    #+#             */
/*   Updated: 2024/01/26 12:10:36 by avedrenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Server.hpp"

std::vector<std::string > split(std::string s, std::string del){
	size_t pos = 0;
	std::vector < std::string > parts;

	while ((pos = s.find_first_of(del)) != std::string::npos){
		std::string token = s.substr(0, pos);
		if (token.size() > 0){
			parts.push_back(token);
		}
		s.erase(0, pos + 1);
	}
	return (parts);
}

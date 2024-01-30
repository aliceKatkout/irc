/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 15:13:01 by avedrenn          #+#    #+#             */
/*   Updated: 2024/01/30 16:43:28 by avedrenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Server.hpp"

std::vector<std::string > split(std::string s, std::string del){
    // Use find function to find 1st position of delimiter.
	std::vector<std::string> res;
    int end = s.find(del);
    while (end != -1) { // Loop until no delimiter is left in the string.
        res.push_back(s.substr(0, end));
        s.erase(s.begin(), s.begin() + end + 1);
        end = s.find(del);
    }
    res.push_back(s.substr(0, end));
	return res;
}

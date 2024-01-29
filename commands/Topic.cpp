/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabourd <mrabourd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 18:05:34 by mrabourd          #+#    #+#             */
/*   Updated: 2024/01/29 18:09:06 by mrabourd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Command.hpp"

void Topic::execute(User *user, std::vector<std::string> args) {
    user->reply("332 " + user->getPrefix() + " :topic" + user->getNickname());

}
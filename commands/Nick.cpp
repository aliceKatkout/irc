/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 14:23:18 by avedrenn          #+#    #+#             */
/*   Updated: 2024/01/25 15:20:32 by avedrenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Command.hpp"

void NickCmd::execute(User *user, std::vector<std::string> args) {
		user->setNickname(args[0]);
		std::cout << "Nickname set to " << user->getNickname() << std::endl;
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 14:23:18 by avedrenn          #+#    #+#             */
/*   Updated: 2024/01/26 10:42:34 by avedrenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Command.hpp"

void NickCmd::execute(User *user, std::vector<std::string> args) {
		user->setNickname(args[1]);
		std::cout << "Nickname set to " << user->getNickname() << "END of nickname" << std::endl;
}
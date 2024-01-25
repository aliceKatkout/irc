/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pass.Cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 14:53:18 by avedrenn          #+#    #+#             */
/*   Updated: 2024/01/25 14:53:28 by avedrenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/Command.hpp"

void PassCmd::execute(User *user, std::vector<std::string> args) {
	if (args.size() == 1) {
		user->setGoodPass(true);
	}
	else {
		// send error
	}
}
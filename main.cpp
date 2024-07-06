/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isouaidi <isouaidi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 19:40:32 by isouaidi          #+#    #+#             */
/*   Updated: 2024/07/06 19:40:33 by isouaidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */





#include "Server.hpp"
#include "Client.hpp"
#include "Utils.hpp"
#include <ncurses.h>

int	main(int argc, char **av)
{
	Server	myServer;
	
	if (base_parsing(argc, av) == -1)
		return (0);
	if (myServer.create_server(myServer, av) == -1)
	{
		std::cout << PROBLEM_CREATING_SERV;
		return (0);
	}
	myServer.principal_loop(myServer, myServer.getVector());
	//close(myClient.getSocket());
	print_amazing();

	myServer.close_server(myServer);
	return (0);
}


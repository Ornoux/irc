/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isouaidi <isouaidi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 19:40:32 by isouaidi          #+#    #+#             */
/*   Updated: 2024/07/08 16:13:44 by isouaidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */





#include "Server.hpp"
#include "Client.hpp"
#include "Utils.hpp"
#include <ncurses.h>

int	main(int argc, char **av)
{
	Server	myServer;
	Client	myClient;
	if (base_parsing(argc, av) == -1)
		return (0);
	if (myServer.create_server(myServer, av) == -1)
	{
		std::cout << PROBLEM_CREATING_SERV;
		return (0);
	}
	//close(myClient.getSocket());
	print_amazing();
	myServer.principal_loop(myClient);
	// myServer.disconnect_clients_from_serv();
	myServer.close_server();
	return (0);
}


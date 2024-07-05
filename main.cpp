/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npatron <npatron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 17:56:51 by npatron           #+#    #+#             */
/*   Updated: 2024/07/05 19:43:42 by npatron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "Client.hpp"

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
	myServer.principal_loop(myServer, myClient);
	close(myClient.getSocket());
	myServer.close_server(myServer);
	return (0);
}


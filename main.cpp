/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isouaidi <isouaidi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 17:56:51 by npatron           #+#    #+#             */
/*   Updated: 2024/07/06 18:44:43 by isouaidi         ###   ########.fr       */
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
	
	unsigned int	 	cslen;
	struct sockaddr_in	csin;
	std::string tmp_password(av[2]);
	int	tmp;
	
	if (base_parsing(argc, av) == -1)
		return (0);
	myServer.setPort(atoi(av[1]));
	myServer.setPassword(tmp_password);
	if (myServer.create_server(myServer) == -1)
	{
		std::cout << PROBLEM_CREATING_SERV;
		return (0);
	}
	int_max(av[1]);
	print_amazing();


	tmp = accept(myServer.getSocket(), (struct sockaddr*)&csin, &cslen);
	myClient.setSocket(tmp);
	close(tmp);
	myServer.close_server(myServer);
	return (0);
}
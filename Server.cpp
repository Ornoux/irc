/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npatron <npatron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 14:13:39 by npatron           #+#    #+#             */
/*   Updated: 2024/07/04 19:15:48 by npatron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

// MEMBER FUNCTIONS

Server::Server() : _port(0), _password("NULL")
{
	return ;
}

Server::~Server()
{
	return ;
}

unsigned int Server::getPort()
{
	return (this->_port);
}

void	Server::setPort(unsigned int port)
{
	this->_port = port;
	return ;
}

std::string Server::getPassword()
{
	return (this->_password);
}

int	Server::getSocket()
{
	return (this->_socket);
}

void	Server::setPassword(std::string password)
{
	this->_password = password;
	return ;
}

int	Server::create_server(Server& myServer)
{
	struct protoent 	*proto;
	struct sockaddr_in 	sin;
	
	proto = getprotobyname("tcp"); // OBTENIR LES INFORMATIONS DU PROTOCOLE TCP
	if (proto == 0)
		return (-1);
	myServer._socket = socket(PF_INET, SOCK_STREAM, proto->p_proto); // CREATION DE LA SOCKET : PF_INET --> iPv4, type de socket SOCK_STREAM
	sin.sin_family = AF_INET;
	sin.sin_port = htons(myServer._port);
	sin.sin_addr.s_addr = htonl(INADDR_ANY);
	bind(myServer._socket, (const struct sockaddr*)&sin, sizeof(sin)); //associe un nom a une socket
	
	listen(myServer._socket, 1);
	return (0);
}

void Server::close_server(Server& myServer)
{
	close(myServer._socket);
}

// OTHER FUNCTIONS

int	valid_port(char *argv)
{
	int count = 0;
	for (int i = 0; argv[i]; i++)
	{
		if (!isdigit(argv[i]))
			return (-1);
		count++;
	}
	if (count != 5)
		return (-1);
	return (0);
}

int base_parsing(int argc, char **argv)
{
	if (argc != 3)
	{
		std::cout << BAD_ARGS;
		return (-1);
	}
	else if (valid_port(argv[1]) == -1)
	{
		std::cout << INVALID_PORT;
		return (-1);
	}
	else
		return (0);
}
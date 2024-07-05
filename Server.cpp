/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npatron <npatron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 14:13:39 by npatron           #+#    #+#             */
/*   Updated: 2024/07/06 00:13:21 by npatron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

// MEMBER FUNCTIONS

bool _loop = true;

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

void	Server::setPassword(char *pass)
{
	std::string tmp_pass(pass);
	this->_password = tmp_pass;
	return ;
}

int	Server::create_server(Server& myServer, char **av)
{
	struct protoent 	*proto;
	struct sockaddr_in 	sin;
	
	proto = getprotobyname("tcp");
	if (proto == 0)
		return (-1);
	myServer.setPort(atoi(av[1]));
	myServer.setPassword(av[2]);
	myServer._socket = socket(PF_INET, SOCK_STREAM, proto->p_proto);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(myServer._port);
	sin.sin_addr.s_addr = htonl(INADDR_ANY);
	bind(myServer._socket, (const struct sockaddr*)&sin, sizeof(sin));
	
	listen(myServer._socket, 1);
	return (0);
}

void Server::principal_loop(Server& myServer, Client& myClient)
{
	accept_client(myServer, myClient);
	while (_loop == true)
	{
		check_signal();	
	}
	return ;
}

void Server::accept_client(Server& myServer, Client& myClient)
{
	unsigned int	 	cslen;
	struct sockaddr_in	csin;
	myClient.setSocket(accept(myServer.getSocket(), (struct sockaddr*)&csin, &cslen));
	return ;
}

void Server::check_signal(void)
{
	signal(SIGINT, signal_action);
	return ;
}

void Server::close_server(Server& myServer)
{
	close(myServer._socket);
	return ;
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

void	signal_action(int s)
{
	(void)s;
	_loop = false;
	std::cout << "OUI LE CONTROLE C" << std::endl;
	return ;
}
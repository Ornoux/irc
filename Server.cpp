/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isouaidi <isouaidi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 14:13:39 by npatron           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/07/06 18:40:42 by npatron          ###   ########.fr       */
=======
/*   Updated: 2024/07/06 18:44:35 by isouaidi         ###   ########.fr       */
>>>>>>> c4b52de (1)
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

// MEMBER FUNCTIONS

bool _loop = true;

Server::Server() : _port(0), _password("NULL"), _clientsConnected(0)
{
	return ;
}

Server::~Server()
{
	return ;
}

// GETTERS / SETTERS

// PORT

unsigned int Server::getPort()
{
	return (this->_port);
}

void	Server::setPort(unsigned int port)
{
	this->_port = port;
	return ;
}

// PASSWORD

std::string Server::getPassword()
{
	return (this->_password);
}

void	Server::setPassword(char *pass)
{
	std::string tmp_pass(pass);
	this->_password = tmp_pass;
	return ;
}

// SOCKET

int	Server::getSocket()
{
	return (this->_socket);
}

// VECTOR

void	Server::setVector(std::vector<Client> vectorClient)
{
	this->_clientList = vectorClient;
}

std::vector<Client>	Server::getVector(void)
{
	return (this->_clientList);
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

void Server::principal_loop(Server& myServer)
{
	accept_client(myServer);
	is_a_valid_client(myServer);
	while (_loop == true)
	{
		check_signal();	
	}
	return ;
}

void Server::accept_client(Server& myServer)
{
	unsigned int	 	cslen;
	struct sockaddr_in	csin;
	myClient.setSocket(accept(myServer.getSocket(), (struct sockaddr*)&csin, &cslen));
	return ;
}

void Server::is_a_valid_client(Server& myServer)
{
	bool valid_client = false;
	while (valid_client == false)
	{
		client_valid_pass(myServer, myClient);
		client_valid_nickname(myServer, myClient);
		client_valid_userline(myServer, myClient);
		client_valid_realname(myServer, myClient);
		break ;
	}
	std::cout << "Client connecté : \n" << myClient;
}

void Server::client_valid_pass(Server& myServer)
{
	(void)myServer._clientsConnected;
	
	char stock[1024];
	int x = 0;
	
	std::string good_pass = "PASS " + myServer._password + "\r\n";
	const char	*tmp_pass = good_pass.c_str();
	std::string message = "Enter : 'PASS <realpass>'\n";
	const char	*message_tmp = message.c_str();
	
	while (1)
	{
		send(myClient.getSocket(), message_tmp, sizeof(message), 0);
		x = recv(myClient.getSocket(), stock, sizeof(stock), 0);
		if (strncmp(stock, tmp_pass, x - 1) == 0)
			break;
	}
}

void Server::client_valid_nickname(Server& myServer
{
	(void)myServer._clientsConnected;
	
	char stock[1024];
	int x = 0;
	
	std::string message = "Enter : 'NICK <nickname>'\n";
	const char	*message_tmp = message.c_str();
	
	while (1)
	{
		send(myClient.getSocket(), message_tmp, sizeof(message), 0);
		x = recv(myClient.getSocket(), stock, sizeof(stock), 0);
		if (strncmp(stock, "NICK ", 5) == 0 && (stock[6] && isalnum(stock[6]) == 0))
		{
			std::string	nickname_tmp(stock + 6);
			std::cout << nickname_tmp << std::endl;
			myClient.setNick(nickname_tmp);
			break;
		}
	}
}

void Server::client_valid_userline(Server& myServer, std::vector<Client> _clientList)
{
	(void)myServer._clientsConnected;
	
	char stock[1024];
	int x = 0;
	
	std::string message = "Enter : 'USER <username>'\n";
	const char	*message_tmp = message.c_str();
	
	while (1)
	{
		send(myClient.getSocket(), message_tmp, sizeof(message), 0);
		x = recv(myClient.getSocket(), stock, sizeof(stock), 0);
		if (strncmp(stock, "USER ", 5) == 0 && (stock[6] && isalnum(stock[6]) == 0))
		{
			std::string	username_tmp(stock + 6);
			std::cout << username_tmp << std::endl;
			myClient.setUser(username_tmp);
			break;
		}
	}
}

void Server::client_valid_realname(Server& myServer, std::vector<Client> _clientList)
{
	(void)myServer._clientsConnected;
	
	char stock[1024];
	int x = 0;
	
	std::string message = "Enter : 'REAL <username>'\n";
	const char	*message_tmp = message.c_str();
	
	while (1)
	{
		send(myClient.getSocket(), message_tmp, sizeof(message), 0);
		x = recv(myClient.getSocket(), stock, sizeof(stock), 0);
		if (strncmp(stock, "REAL ", 5) == 0 && (stock[6] && isalnum(stock[6]) == 0))
		{
			std::string	realname_tmp(stock + 6);
			std::cout << realname_tmp << std::endl;
			myClient.setRealName(realname_tmp);
			break;
		}
	}
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

int	int_max(char *str)
{
	int digits;
	digits = atoi(str);
	if (digits < 1 || digits > 65535)
		return 1;
	return 0;
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
	else if(int_max(argv[1]) == 1)
	{
		std::cout << BAD_PORT;
		return (-1);
	}
		return (0);
}

void	signal_action(int s)
{
	(void)s;
	_loop = false;
	return ;
}

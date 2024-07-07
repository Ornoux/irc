/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npatron <npatron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 14:13:39 by npatron           #+#    #+#             */
/*   Updated: 2024/07/07 15:18:04 by npatron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

// MEMBER FUNCTIONS

bool _loop = true;

Server::Server() : _port(0), _password("NULL"), _nbClients(0)
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

void	Server::setSocket(int sock)
{
	this->_socket = sock;
	return ;
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

void Server::principal_loop(Client& myClient)
{
	while (_loop == true)
	{
		fd_set readfds;
		FD_ZERO(&readfds);
		FD_SET(_socket, &readfds);
		select(_socket + 1, &readfds, NULL, NULL, NULL);
		if (FD_ISSET(_socket, &readfds))
		{
			accept_client(myClient);
			is_a_valid_client(myClient);
		}
		check_signal();
	}
	return ;
}

void Server::accept_client(Client& myClient)
{
	unsigned int	 	cslen;
	struct sockaddr_in	csin;
	myClient.setSocket(accept(getSocket(), (struct sockaddr*)&csin, &cslen));
	return ;
}

void Server::is_a_valid_client(Client& myClient)
{
	bool valid_client = false;
	while (valid_client == false)
	{
		client_valid_pass(myClient);
		client_valid_nickname(myClient);
		client_valid_userline(myClient);
		client_valid_realname(myClient);
		_clientList.push_back(myClient);
		_nbClients++;
		break ;
	}
	std::cout << "Numbers of clients connected : " << _nbClients << std::endl;
	print_client_vector();
}

void Server::client_valid_pass(Client& myClient)
{

	char stock[1024];
	int x = 0;
	
	std::string good_pass = "PASS " + _password + "\r\n";
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

void Server::client_valid_nickname(Client& myClient)
{	
	char stock[1024];
	int x = 0;
	
	std::string message = "Enter : 'NICK <nickname>'\n";
	const char	*message_tmp = message.c_str();
	
	while (1)
	{
		send(myClient.getSocket(), message_tmp, sizeof(message), 0);
		x = recv(myClient.getSocket(), stock, sizeof(stock), 0);
		if (strncmp(stock, "NICK ", 5) == 0)
		{
			std::string	nickname_tmp(stock + 5);
			std::cout << nickname_tmp << std::endl;
			myClient.setNick(nickname_tmp);
			break;
		}
	}
}

void Server::client_valid_userline(Client& myClient)
{
	char stock[1024];
	int x = 0;
	
	std::string message = "Enter : 'USER <username>'\n";
	const char	*message_tmp = message.c_str();
	
	while (1)
	{
		send(myClient.getSocket(), message_tmp, sizeof(message), 0);
		x = recv(myClient.getSocket(), stock, sizeof(stock), 0);
		if (strncmp(stock, "USER ", 5) == 0)
		{
			std::string	username_tmp(stock + 5);
			std::cout << username_tmp << std::endl;
			myClient.setUser(username_tmp);
			break;
		}
	}
}

void Server::client_valid_realname(Client& myClient)
{	
	char stock[1024];
	int x = 0;
	
	std::string message = "Enter : 'REAL <username>'\n";
	const char	*message_tmp = message.c_str();
	
	while (1)
	{
		send(myClient.getSocket(), message_tmp, sizeof(message), 0);
		x = recv(myClient.getSocket(), stock, sizeof(stock), 0);
		if (strncmp(stock, "REAL ", 5) == 0)
		{
			std::string	realname_tmp(stock + 5);
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

void Server::close_server()
{
	close(_socket);
	return ;
}

void Server::disconnect_clients_from_serv()
{
	int count = 0;

	for (int i = 0; count != _nbClients; i++)
	{
		if (_clientList[i].getSocket())
		{
			std::cout << _clientList[i].getNick() << " disconnected" << std::endl;
			close(_clientList[i].getSocket());
			count++;
			_nbClients--;
			std::cout << "Client connected : " << _nbClients << std::endl;
		}
	}
	return ;
}

void Server::print_client_vector()
{
	for (int i = 0; i != _nbClients; i++)
	{
		std::cout << "---------------------" << std::endl;
		std::cout << "SOCKET : " << _clientList[i].getSocket() << std::endl;
		std::cout << "USER : " << _clientList[i].getUser() << std::endl;
		std::cout << "NICK : " << _clientList[i].getNick() << std::endl;
		std::cout << "REALNAME : " << _clientList[i].getRealName() << std::endl;
		std::cout << "---------------------" << std::endl;
	}
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
	return ;
}

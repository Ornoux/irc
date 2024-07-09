/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npatron <npatron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 14:13:39 by npatron           #+#    #+#             */
/*   Updated: 2024/07/09 18:32:42 by npatron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "Utils.hpp"
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

void	Server::launch_serv(char **av)
{
    struct protoent 	*proto;
	struct sockaddr_in 	sin;
	proto = getprotobyname("tcp");
	if (proto == 0)
		return ;
	setPort(atoi(av[1]));
	setPassword(av[2]);
	_socket = socket(PF_INET, SOCK_STREAM, proto->p_proto);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(_port);
	sin.sin_addr.s_addr = htonl(INADDR_ANY);
	bind(_socket, (const struct sockaddr*)&sin, sizeof(sin));
	
	listen(_socket, 10);
}

void    Server::loop_test(char **av, Client myClient)
{
	fd_set readfds;
	int max_sd;
	int cs;
	int connexion;
	char buff[1024];
	int ret;
	
	launch_serv(av);
	print_amazing();
	std::cout << "Server launched" << std::endl;
	while (true)
	{
		FD_ZERO(&readfds);
		FD_SET(_socket, &readfds);
		max_sd = _socket;
		for (size_t i = 0; i < _clientVector.size(); i++)
		{
			cs = _clientVector[i].getSocket();
			if (cs > 0)
				FD_SET(cs, &readfds);
			if (cs > max_sd)
				max_sd = cs;
		}
		connexion = select(max_sd + 1, &readfds, NULL, NULL, NULL);
		if (connexion < 0)
			throw(SelectError());
		if (FD_ISSET(_socket, &readfds)) // RECOIT UNE CONNEXION
			AddClientToVector(myClient);
		for (size_t i = 0; i < _clientVector.size(); i++)
		{
			cs = _clientVector[i].getSocket();
			if (FD_ISSET(cs, &readfds))
			{
				ret = recv(cs, buff, 1024, 0);
				buff[ret] = '\0';
				std::cout << buff << std::endl;
				if (ret == 0)
					DeleteClientFromServ(i);
				else
					SendDataToClient(cs, std::string(buff));
			}
		}
	}
	return ;
}

void	Server::AddClientToVector(Client myClient)
{
	struct sockaddr_in	csin;
	unsigned int	 	cslen = sizeof(csin);
	int socket_client;
	
	socket_client = accept(_socket, (struct sockaddr*)&csin, &cslen);
	std::cout << socket_client;
	if (socket_client < 0)
		throw(AcceptError());
	myClient.setSocket(socket_client);
	_clientVector.push_back(myClient);
	_nbClients++;
	std::cout << "Client accepted" << std::endl;
	return ;
}

void	Server::printClient()
{
	for (size_t i = 0; i < _clientVector.size(); i++)
	{
		std::cout << "FD : " << _clientVector[i].getSocket() << std::endl;
		
	}
	return ;
}

void	Server::SendDataToClient(int fd, std::string msg)
{
	send(fd, msg.c_str(), msg.size(), 0);
	return ;
}

bool check_cara(char c, char *str){
	std::string st1(str);
	int i = 0;

	while(str[i] != '\r')
	{
		if (str[i] == c){
			std::cout << "ok = "<<i << std::endl;
			return true;
		}
		i++;
	}
	return false;
}

void Server::client_valid_pass(Client& myClient)
{

	char stock[1024];
	int x = 0;
	
	std::string good_pass ="PASS " + _password + "\r\n";
	// const char	*tmp_pass = good_pass.c_str();
	// std::string	stock0(stock);
	std::string message = "Enter : 'PASS <realpass>'\n";
	const char	*message_tmp = message.c_str();
	
	while (1)
	{
		send(myClient.getSocket(), message_tmp, sizeof(message), 0);
		x = recv(myClient.getSocket(), stock, sizeof(stock), 0);
		stock[x - 1] = '\r';
		stock[x ] = '\n';
		stock[x + 1] = '\0';
		std::string	stock0(stock);
		std::cout << "GP " << good_pass << std::endl;
		std::cout << "stock " << stock0 << std::endl;
		// std::cout <<" x - 6 = " << x - 6 << std::endl;
		// std::cout <<" x = " << x << std::endl;
		//std::cout <<" len tmp =" << strlen(tmp_pass) << std::endl;
		// std::cout <<" len stock =" << strlen(stock)<< std::endl;
		// std::cout <<" len stock -5 =" << strlen(stock) - 5 << std::endl;
		// std::cout << this->_password << std::endl;
		// std::cout << " reslt " <<strncmp(tmp_pass, stock0, x - 6) << std::endl;
		// if (strncmp(stock, "PASS ", 5) == 0 
		// 	&& strncmp(tmp_pass, stock0, (strlen(tmp_pass))) == 0 
		// 	&& ((strlen(stock) - 6) == strlen(tmp_pass)))
		if (good_pass == stock0)
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
		stock[x - 1] = '\r';
		stock[x] = '\n';
		stock[x + 1] = '\0';
		// std::cout << "stock 2 " << x - 6 << std::endl;
		// std::cout << "cara " << check_cara(' ', stock + 5)  << std::endl;
		if (strncmp(stock, "NICK ", 5) == 0  
			&& (check_cara(' ', stock + 5) == 0) && (x - 6)> 0)
		{
			std::string	nickname_tmp(stock + 5);
			std::cout << nickname_tmp << std::endl;
			myClient.setNick(nickname_tmp);
			break;
		}
	}
}

void	Server::DeleteClientFromServ(int i)
{
	std::cout << "Host disconnected: " << _clientVector[i].getSocket() << std::endl;
	close(_clientVector[i].getSocket());
	_clientVector.erase(_clientVector.begin() + i);
}

void Server::client_valid_username(Client& myClient)
{
	char stock[1024];
	int x = 0;
	
	std::string message = "Enter : 'USER <username>'\n";
	const char	*message_tmp = message.c_str();
	
	while (1)
	{
		send(myClient.getSocket(), message_tmp, sizeof(message), 0);
		x = recv(myClient.getSocket(), stock, sizeof(stock), 0);
		stock[x - 1] = '\r';
		stock[x] = '\n';
		stock[x + 1] = '\0';
		if (strncmp(stock, "USER ", 5) == 0 
			&& (check_cara(' ', stock + 5) == 0) && (x - 6) > 0)
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
		stock[x - 1] = '\r';
		stock[x] = '\n';
		stock[x + 1] = '\0';
		if (strncmp(stock, "REAL ", 5) == 0 
			&& (check_cara(' ', stock + 5) == 0) && (x - 6 ) > 0)
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


// OTHER FUNCTIONS

void	signal_action(int s)
{
	(void)s;
	std::cout << "CONTROLE C VALIDE" << std::endl;
	_loop = false;
	return ;
}

// OTHER FUNCTIONS

int		valid_port(char *argv)
{
	if (atoi(argv) != 6661 && atoi(argv) != 6662 && atoi(argv) != 6663 && atoi(argv) != 6664 \
		&& atoi(argv) != 6665 && atoi(argv) != 6666 && atoi(argv) != 6667 && atoi(argv) != 6668 \
		&& atoi(argv) != 6669)
		return (-1);
	return (0);
}

void	base_parsing(int argc, char **argv)
{
	if (argc != 3)
		throw(BadArgs());
	else if (valid_port(argv[1]) == -1)
		throw(BadPort());
	return ;
}
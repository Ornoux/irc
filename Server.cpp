/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npatron <npatron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 14:13:39 by npatron           #+#    #+#             */
/*   Updated: 2024/07/10 14:47:51 by npatron          ###   ########.fr       */
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

void    Server::loop(char **av, Client myClient)
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
					getCmd(cs, std::string(buff));
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
		if (_clientVector[i].getBoolPass() == true)
			std::cout << "PASS: Valid." << std::endl;
		else
			std::cout << "PASS: Invalid." << std::endl;
	}
	return ;
}

void	Server::getCmd(int fd, std::string msg)
{
	std::vector<std::string> vectorInput;
	std::string delimiter = "\r\n";
	size_t ret;
	
	ret = msg.find(delimiter);
	if (ret == std::string::npos)
	{
		vectorInput.push_back(msg);
	}
	else
	{
		while ((ret = msg.find(delimiter)) != std::string::npos)
		{
			std::string lineToAdd = msg.substr(0, ret);
			msg = msg.substr(ret + delimiter.length());
			vectorInput.push_back(lineToAdd);
		}
	}
	treatVectorCmd(fd, vectorInput);
	return ;
}

void	Server::treatVectorCmd(int fd, std::vector<std::string> vectorCmd)
{
	std::string cmd;
	std::string test;
	(void)fd;
	for (size_t i = 0; i < vectorCmd.size(); i++)
	{
		cmd = vectorCmd[i];
		if ((cmd.compare(0, 4, "PASS")) == 0)
			getPass(fd, cmd);
		// else if ((cmd.compare(0, 5, "NICK ")) == 0)
		// 	//GET NICK
		// else if ((cmd.compare(0, 5, "USER ")) == 0)
		// 	// GET USER
		else
			std::cout << "OKAY" << std::endl;
	}
	printClient();
}

int	Server::findClientByFd(int fd)
{
	int	client_socket = 0;
	for (size_t i = 0; i < _clientVector.size(); i++)
	{
		client_socket = _clientVector[i].getSocket();
		if (client_socket == fd)
			return (i);
	}
	throw(FindClient());
}

void	Server::isAuthenticate(Client myClient)
{
	if (myClient.getBoolNick() == true && myClient.getBoolUser() == true
		&& myClient.getBoolPass() == true)
		myClient.setBoolAuthenticate(true);
	return ;
}

// void	Server::getNick(int fd, std::string cmd)
// {
// 	Client	myClient = findClientByFd(fd);
// 	std::string tmp = cmd.substr(6);
// }

void	Server::getPass(int fd, std::string cmd)
{
	int	client = findClientByFd(fd);
	
	std::string replie_tmp = "PASS :" + std::string(ERR_NEEDMOREPARAMS);
	const char *replie = replie_tmp.c_str();
	
	std::cout << strlen(replie) << std::endl;
	if (cmd.size() == 5)
		send(fd, replie, strlen(replie), 0);
	else if (_clientVector[client].getBoolPass() == true
			|| _clientVector[client].getBoolAuthenticate() == true)
	{
		replie_tmp = "PASS :" + std::string(ERR_ALREADYREGISTRED);
		replie = replie_tmp.c_str();
		send(fd, replie, strlen(replie), 0);
	}
	else
	{
		std::string good_pass = "PASS " + _password + "\n";

		if (cmd.compare(good_pass) == 0)
			_clientVector[client].setBoolPass(true);
		isAuthenticate(_clientVector[client]);
	}
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
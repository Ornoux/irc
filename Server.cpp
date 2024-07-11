/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npatron <npatron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 14:13:39 by npatron           #+#    #+#             */
/*   Updated: 2024/07/11 21:15:10 by npatron          ###   ########.fr       */
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
		if ((cmd.compare(0, 5, "PASS ")) == 0)
			getPass(fd, cmd);
		else if ((cmd.compare(0, 5, "JOIN ")) == 0)
			handleChannels(fd, cmd);
		else
			std::cout << "OKAY" << std::endl;
	}
	printClient();
}

// JOIN #channel1,#channel2 fubar,foobar

void	Server::handleChannels(int fd, std::string cmd)
{
	std::vector<std::string> namesChannels = splitCmdNameChannels(cmd);
	std::vector<std::string> passwordsChannels = splitCmdPasswordChannels(cmd);
	Client myClient = findClientByFd(fd);
	std::string channelName;
	int	nbPasswords = passwordsChannels.size();
	
	// VERIF NAMES CHANNELS
	for (size_t i = 0; i , namesChannels.size(); i++)
	{
		if (channelNameIsAcceptable(namesChannels[i]) == false)
		{
			myClient.sendErrorRPL(namesChannels[i], ERR_BADCHANMASK);
			return ;
		}
	}
	for (size_t i = 0; i < namesChannels.size(); i++)
	{
		channelName = namesChannels[i];
		if (myClient.isInChannel(namesChannels[i]) == true) // ERROR// CLIENT DANS LE CHANNEL //
		{
			myClient.sendErrorRPL(myClient.getNick() + " " + namesChannels[i], ERR_USERONCHANNEL);
			return ;
		}
		if (channelAlreadyExists(channelName) == false) // CHANNEL N'EXISTE PAS --> 
		{
			Channel *myChannel = new Channel();
			myChannel->setName(channelName);
			if (i <= nbPasswords)
				myChannel->setPassword(passwordsChannels[i]);
			myChannel->addClientToChannel(myClient);
			myChannel->addClientOperatorToChannel(myClient);
			_channelVector.push_back(myChannel);
		}
		else // CANAL EXISTS
		{
			Channel *myChannel = findChannelByName(channelName);
			if (myChannel->hasPassword() == true) // IF CANAL NEEDS PASSWORD
			{
				if (i <= nbPasswords) // PASSWORD GIVED
				{
					if (passwordsChannels[i] != myChannel->getPassword()) // BAD PASSWORD
					{
						myClient.sendErrorRPL(channelName, ERR_BADCHANNELKEY);
						return ;
					}
					else
						myChannel->addClientToChannel(myClient);
				}
				else // PASSWORD NOT GIVED WHILE IT REQUIRED
				{
					myClient.sendErrorRPL(channelName, ERR_BADCHANNELKEY);
					return ;
				}
			}
			else // CANAL EXISTS BUT DOESN'T NEED A PASSWORD
			{
				if (i <= nbPasswords)
				{
					myClient.sendErrorRPL(channelName, ERR_KEYSET);
					return ;
				}	
				else
					myChannel->addClientToChannel(myClient);
			}
		}
		
	}	
}

bool	Server::channelAlreadyExists(std::string channel)
{
	for (size_t i = 0; i < _channelVector.size(); i++)
	{
		if (channel == _channelVector[i]->getName())
			return (true);
	}
	return (false);
}

std::vector<std::string>	Server::splitCmdPasswordChannels(std::string cmd)
{
	size_t ret = 0;

	std::string stock;
	std::vector<std::string> vectorPassword;
	std::string delimiter = ",";
	
	stock = cmd.substr(5);
	ret = stock.find(" ");
	if (ret == std::string::npos)
	{
		return (vectorPassword);
	}
	else
	{
		stock = stock.substr(ret + 1);
		std::cout << "Password stock : " << stock << std::endl;
		while ((ret = stock.find(delimiter)) != std::string::npos)
		{
			std::string lineToAdd = stock.substr(0, ret);
			stock = stock.substr(ret + delimiter.length());
			vectorPassword.push_back(lineToAdd);
		}
		vectorPassword.push_back(stock);
	}
	return (vectorPassword);
}

std::vector<std::string>	Server::splitCmdNameChannels(std::string cmd)
{
	size_t ret = 0;

	std::string stock;
	std::vector<std::string> vectorChannels;
	std::string delimiter = ",";
	size_t	space = 0;
	
	stock = cmd.substr(5);
	ret = stock.find(" ");
	space = ret;
	if (ret == std::string::npos)
	{
		ret = stock.find(delimiter);
		if (ret == std::string::npos)
		{
			vectorChannels.push_back(stock);
			return (vectorChannels);
		}
		else
		{
			while ((ret = stock.find(delimiter)) != std::string::npos)
			{
					std::string lineToAdd = stock.substr(0, ret);
					stock = stock.substr(ret + delimiter.length());
					vectorChannels.push_back(lineToAdd);
			}
			std::string lineToAdd = stock.substr(0, space);
			vectorChannels.push_back(lineToAdd);
		}
		return (vectorChannels);
	}
	else
	{
		stock = stock.substr(0, ret);
		std::cout << "Name stock : " << stock << std::endl;
		while ((ret = stock.find(delimiter)) != std::string::npos)
		{
				std::string lineToAdd = stock.substr(0, ret);
				stock = stock.substr(ret + delimiter.length());
				vectorChannels.push_back(lineToAdd);
		}
		std::string lineToAdd = stock.substr(0, space);
		vectorChannels.push_back(lineToAdd);
	}
	return (vectorChannels);
}

Channel *Server::findChannelByName(std::string name)
{
	for (size_t i = 0; _channelVector.size(); i++)
	{
		if (_channelVector[i]->getName() == name)
			return (_channelVector[i]);
	}
	return (NULL);
}

Client	Server::findClientByFd(int fd)
{
	int	client_socket = 0;
	for (size_t i = 0; i < _clientVector.size(); i++)
	{
		client_socket = _clientVector[i].getSocket();
		if (client_socket == fd)
			return (_clientVector[i]);
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

void	Server::getPass(int fd, std::string cmd)
{
	Client myClient = findClientByFd(fd);
	
	std::string replie_tmp = "PASS :" + std::string(ERR_NEEDMOREPARAMS);
	const char *replie = replie_tmp.c_str();
	
	std::cout << strlen(replie) << std::endl;
	if (cmd.size() == 5)
		send(fd, replie, strlen(replie), 0);
	else if (myClient.getBoolPass() == true
			|| myClient.getBoolAuthenticate() == true)
	{
		replie_tmp = "PASS :" + std::string(ERR_ALREADYREGISTRED);
		replie = replie_tmp.c_str();
		send(fd, replie, strlen(replie), 0);
	}
	else
	{
		std::string good_pass = "PASS " + _password + "\n";

		if (cmd.compare(good_pass) == 0)
			myClient.setBoolPass(true);
		isAuthenticate(myClient);
	}
	return ;
}

void	Server::DeleteClientFromServ(int i)
{
	std::cout << "Host disconnected: " << _clientVector[i].getSocket() << std::endl;
	close(_clientVector[i].getSocket());
	_clientVector.erase(_clientVector.begin() + i);
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

// PASSWORD / CHANNEL PARSING CHARACTERS BASIC FUNCTIONS

bool	charAcceptableNameChannel(char c)
{
	if (c == ',' || c == ':' || c == '#'
		|| c == '&' || c == '+' || c == '!')
		return (false);
	return (true);
}
bool	Server::channelNameIsFree(std::string cmd)
{
	for (size_t i = 0; i < _channelVector.size(); i++)
	{
		if (_channelVector[i]->getName() == cmd)
			return (false);		
	}
	return (true);
}

bool	Server::channelNameIsAcceptable(std::string cmd)
{
	if (cmd.size() < 2)
		return (false);
	if (cmd[0] != '#' && cmd[0] != '&' && cmd[0] != '!' && cmd[0] != '+')
		return (false);
	for (size_t i = 1; i < cmd.size(); i++)
	{
		if (charAcceptableNameChannel(cmd[i]) == false)
			return (false);
	}
	return (true);
}

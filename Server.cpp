/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npatron <npatron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 14:13:39 by npatron           #+#    #+#             */
/*   Updated: 2024/07/13 13:32:41 by npatron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "Utils.hpp"
#include "Server.hpp"

// MEMBER FUNCTIONS

bool _loop = true;

Server::Server() : _port(0), _nbClients(0), _password("NULL")
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

void    Server::loop(char **av)
{
	fd_set readfds;
	int max_sd;
	int cs;
	int connexion;
	char buff[1024];
	int ret;
	Client *myClient = new Client();
	(void)myClient;
	launch_serv(av);
	print_amazing();
	std::cout << GRAS << "Server launched\n" << std::endl;
	while (true)
	{
		FD_ZERO(&readfds);
		FD_SET(_socket, &readfds);
		max_sd = _socket;
		for (size_t i = 0; i < _clientVector.size(); i++)
		{
			cs = _clientVector[i]->getSocket();
			if (cs > 0)
				FD_SET(cs, &readfds);
			if (cs > max_sd)
				max_sd = cs;
		}
		connexion = select(max_sd + 1, &readfds, NULL, NULL, NULL);
		if (connexion < 0)
			throw(SelectError());
		if (FD_ISSET(_socket, &readfds)) // RECOIT UNE CONNEXION
			myClient = AddClientToVector();
		for (size_t i = 0; i < _clientVector.size(); i++)
		{
			cs = _clientVector[i]->getSocket();
			if (FD_ISSET(cs, &readfds))
			{
				ret = recv(cs, buff, 1024, 0);
				buff[ret] = '\0';
				if (ret == 0)
					DeleteClientFromServ(i);
				else
					getCmd(cs, std::string(buff));
			}
		}
	}
	return ;
}

Client*	Server::AddClientToVector()
{
	Client *myClient = new Client();
	struct sockaddr_in	csin;
	unsigned int	 	cslen = sizeof(csin);
	int socket_client;
	
	socket_client = accept(_socket, (struct sockaddr*)&csin, &cslen);
	if (socket_client < 0)
		throw(AcceptError());
	myClient->setSocket(socket_client);
	_clientVector.push_back(myClient);
	_nbClients++;
	_logger.logInfo("New client connection");
	return (myClient);
}

void	Server::printClient()
{
	for (size_t i = 0; i < _clientVector.size(); i++)
	{
		std::cout << "FD : " << _clientVector[i]->getSocket() << std::endl;
		if (_clientVector[i]->getBoolPass() == true)
			std::cout << "PASS: Valid." << std::endl;
		else
			std::cout << "PASS: Invalid." << std::endl;
		if (_clientVector[i]->getBoolNick() == true)
			std::cout << "NICK: Valid." << std::endl;
		else
			std::cout << "NICK: Invalid." << std::endl;
		
		if (_clientVector[i]->getBoolUser() == true)
			std::cout << "USER: Valid." << std::endl;
		else
			std::cout << "USER: Invalid." << std::endl;
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
		msg = msg.substr(0, msg.size() - 1);
		_logger.logInput(msg);
		vectorInput.push_back(msg);
	}
	else
	{
		_logger.logInput(msg);
		while ((ret = msg.find(delimiter)) != std::string::npos)
		{
			std::string lineToAdd = msg.substr(0, ret);
			msg = msg.substr(ret  + delimiter.length());
			vectorInput.push_back(lineToAdd);
		}
		vectorInput.push_back(msg);
	}
	treatVectorCmd(fd, vectorInput);
	return ;
}

std::vector<std::string>	Server::splitString(std::string cmd, std::string delimiter)
{
	std::vector<std::string> myVector;
	size_t					 ret;
	std::string 			 stock = cmd;
	 
	ret = stock.find(delimiter);
	if (ret == std::string::npos)
	{
		myVector.push_back(stock);
		return (myVector);
	}
	else
	{
		while ((ret = stock.find(delimiter)) != std::string::npos)
		{
			std::string lineToAdd = stock.substr(0, ret);
			stock = stock.substr(ret + delimiter.length());
			myVector.push_back(lineToAdd);
		}
		myVector.push_back(stock);
	}
	return (myVector);
}

void	Server::treatVectorCmd(int fd, std::vector<std::string> vectorCmd)
{
	std::string cmd;
	std::vector<std::string> vectorSplit;
	for (size_t i = 0; i < vectorCmd.size(); i++)
	{
		cmd = vectorCmd[i];
		vectorSplit = splitString(cmd, " ");
		if ((cmd.compare(0, 4, "PASS")) == 0)
			checkPass(fd, cmd);
		else if ((cmd.compare(0, 4, "NICK")) == 0)
			checkNick(fd, cmd);
		else if ((cmd.compare(0, 4, "USER")) == 0)
			checkUser(fd,cmd);
		else if ((vectorSplit[0] == "JOIN" && vectorSplit.size() != 1))
			handleChannels(fd, cmd.substr(5));
	}
}


void	Server::handleChannels(int fd, std::string cmd)
{
	std::vector<std::string> vectorEverything = splitString(cmd, " ");
	size_t	nbPasswords;
	std::string channelName;
	std::vector<std::string> namesChannels;
	std::vector<std::string> passwordsChannels;
	bool					passwordGived = false;
	std::cout << vectorEverything.size() << std::endl;

	if (vectorEverything.size() == 2)
	{
		namesChannels = splitString(vectorEverything[0], ",");
		passwordsChannels = splitString(vectorEverything[1], ",");
		if (passwordsChannels.empty() == false)
			nbPasswords = passwordsChannels.size() - 1;
		passwordGived = true;
	}
	else if (vectorEverything.size() == 1)
		namesChannels = splitString(vectorEverything[0], ",");
	else
		return ;
	Client *myClient = findClientByFd(fd);

	for (size_t i = 0; i < namesChannels.size(); i++)
	{
		if (channelNameIsAcceptable(namesChannels[i]) == false)
		{
			myClient->sendRPL(namesChannels[i], ERR_BADCHANMASK);
			return ;
		}
	}

	for (size_t i = 0; i < namesChannels.size(); i++)
	{
		channelName = namesChannels[i];
		if (myClient->isInChannel(namesChannels[i]) == true) // ERROR// CLIENT DANS LE CHANNEL //
		{
			myClient->sendRPL(myClient->getNick() + " " + namesChannels[i], ERR_USERONCHANNEL);
			return ;
		}
		if (channelAlreadyExists(channelName) == false) // CHANNEL N'EXISTE PAS --> 
		{
			Channel *myChannel = new Channel();
			myChannel->setName(channelName);
			if (passwordGived == true)
			{
				if (i <= nbPasswords)
				{
					myChannel->setPassword(passwordsChannels[i]);
				}
			}
			myClient->addToChannel(myChannel);
			myChannel->addClientToChannel(myClient);
			myChannel->addClientOperatorToChannel(myClient);
			_channelVector.push_back(myChannel);
			std::cout << "Channel created.\n";
			myChannel->printInfos();
		}
		else // CANAL EXISTS
		{
			Channel *myChannel = findChannelByName(channelName);
			if (myChannel->hasPassword() == true) // IF CANAL NEEDS PASSWORD
			{
				if (passwordGived == true)
				{
					if (i <= nbPasswords) // PASSWORD GIVED
					{
						if (passwordsChannels[i] != myChannel->getPassword()) // BAD PASSWORD
						{
							myClient->sendRPL(channelName, ERR_BADCHANNELKEY);
							return ;
						}
						else
						{
							std::cout << "Client " << myClient->getUser() << " successfully added to " << channelName << std::endl;
							myChannel->addClientToChannel(myClient);
						}
					}
				}
				else // PASSWORD NOT GIVED WHILE IT REQUIRED
				{
					myClient->sendRPL(channelName, ERR_BADCHANNELKEY);
					return ;
				}
			}
			else // CANAL EXISTS BUT DOESN'T NEED A PASSWORD
			{
				if (passwordGived == true)
				{
					if (i <= nbPasswords)
					{
						myClient->sendRPL(channelName, ERR_KEYSET);
						return ;
					}
				}
				else
				{
					std::cout << "Client " << myClient->getUser() << " successfully added to " << channelName << std::endl;
					myChannel->addClientToChannel(myClient);
				}
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


Channel*	Server::findChannelByName(std::string name)
{
	for (size_t i = 0; _channelVector.size(); i++)
	{
		if (_channelVector[i]->getName() == name)
			return (_channelVector[i]);
	}
	return (NULL);
}

Client*		Server::findClientByFd(int fd)
{
	int	client_socket = 0;
	for (size_t i = 0; i < _clientVector.size(); i++)
	{
		client_socket = _clientVector[i]->getSocket();
		if (client_socket == fd)
			return (_clientVector[i]);
	}
	return (NULL);
}

void	Server::isAuthenticate(Client *myClient)
{
	if (myClient->getBoolNick() == true && myClient->getBoolUser() == true
		&& myClient->getBoolPass() == true)
	{
		myClient->setBoolAuthenticate(true);
		myClient->sendRPL("Welcome to the Internet Relay Network ", std::string(myClient->getNick() + "!" + myClient->getUser() + "@127.0.0.1:" + "\r\n").c_str());
	}
	return ;
}

void	Server::checkPass(int fd, std::string cmd)
{
	Client* myClient = findClientByFd(fd);
	
	const char *cmd_c = cmd.c_str();
	
	if (myClient->getBoolPass() == true)
	{
		myClient->sendRPL("PASS", ERR_ALREADYREGISTRED);
		return ;
	}
	else if (strlen(cmd_c) - 5 == 0 )
		myClient->sendRPL("PASS", ERR_NEEDMOREPARAMS);
	else if (checkSpace(' ', cmd_c + 5) == 1)
		return;
	else
	{
		std::string good_pass = "PASS " + _password;
		if (cmd.compare(good_pass) == 0 ){
			myClient->setBoolPass(true);
			_logger.logAccept("PASS");
		}
	}
	return ;
}
bool	Server::similarNick(const char *nick){
	
	std::string nick_s(nick);
	for (size_t i = 0; i < this->_clientVector.size(); i++)
	{	
		if((this->_clientVector[i]->getNick()) == nick_s)
			return true;
	}
	return false;
}
void	Server::checkNick(int fd, std::string cmd)
{
	Client *myClient = findClientByFd(fd);
	
	const char *cmd_c = cmd.c_str();  
	
	if (myClient->getBoolPass() == true &&
		myClient->getBoolUser() == false)
	{
		if (myClient->getBoolNick() == true)
			myClient->sendRPL("NICK", ERR_ERRONEUSNICKNAME);
		else if (strncmp((cmd_c + 4), " " , 1) != 0)
			return;
		else if (strlen(cmd_c) - 5 == 0)
			myClient->sendRPL("NICK", ERR_NONICKNAMEGIVEN);
		else if (checkNormeCara(cmd_c + 5) == 1 || strlen(cmd_c + 5) > 10 
			|| ( checkSpace(' ', cmd_c + 5) == 1 ))
			myClient->sendRPL("NICK", ERR_ERRONEUSNICKNAME);
			
		else
		{
			if (similarNick((cmd_c + 5)) == true){
				myClient->sendRPL("NICK", ERR_NICKNAMEINUSE);
				return;
			}
			_logger.logAccept("NICK");
			std::string nickReal((cmd_c + 5));
			myClient->setBoolNick(true);
			myClient->setNick(nickReal);
				
		}		
	}
	return; 
}

void	Server::checkUser(int fd, std::string cmd)
{
	Client *myClient = findClientByFd(fd);
	
	const char *cmd_c = cmd.c_str(); 
	std::string cmd_s(cmd_c);
	
	if (myClient->getBoolUser() == true)
	{
		myClient->sendRPL("USER", ERR_ALREADYREGISTRED);
		return;
	}
	
	size_t start = 5;
	size_t end = cmd_s.find(' ', start);
	if (end == std::string::npos)
	{
		myClient->sendRPL("NICK", ERR_NEEDMOREPARAMS);
		return ;
	}
	
	std::string userReal = cmd_s.substr(start, end - start);
	const char *ureal_c = userReal.c_str();
	std::string ope = cmd_s.substr(end, 6);
	
	if (ope != " 0 * :")
		return;
	
	std::string realname((cmd_c + end + 6));
	const char *real_c = realname.c_str(); 
	
	if (myClient->getBoolPass() == true
		&& myClient->getBoolNick() == true)
	{
		if (strncmp((cmd_c + 4), " " , 1) != 0)
			return;
		else if (strlen(cmd_c) - 5 == 0)
			myClient->sendRPL("NICK", ERR_ERRONEUSNICKNAME);
		else if (checkNormeCara(ureal_c) == 1 || checkNormeCara(real_c) == 1
			|| ( checkSpace(' ', ureal_c) == 1 ) || (checkSpace(' ', real_c) == 1))
			return;
		else
		{
			_logger.logAccept("USER");
			myClient->setBoolUser(true);
			myClient->setUser(userReal);
			myClient->setRealName(realname);
			isAuthenticate(myClient);
			myClient->printInfos();
		}
	}
	return; 
}

bool checkNormeCara(const char *str){
    
	size_t i = 0;
	
    if (!((str[0] >= 'A' && str[0] <= 'Z') || (str[0] >= 'a' && str[0] <= 'z'))) 
        return true;
		 
    while (i < strlen(str) - 1) {
        if (!((str[i] >= '0' && str[i] <= '9') || (str[i] >= 'a' && str[i] <= 'z') || 
			  (str[i] >= 'A' && str[i] <= 'Z') || str[i] == '-' || str[i] == '[' || str[i] == ']' || 
              str[i] == '\\' || str[i] == '^' || str[i] == '{' || str[i] == '}' || 
              str[i] == '_')) {
            return true;
        }
        i++;
    }

    return false;
}
bool checkSpace(char c, const char *str){
	int i = 0;

	while(str[i])
	{
		if (str[i] == c)
			return true;
		i++;
	}
	return false;
}

void	Server::DeleteClientFromServ(int i)
{
	_logger.logInfo("Client disconnected");
	close(_clientVector[i]->getSocket());
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

void	printStringVector(std::vector<std::string> myVector)
{
	for (size_t i = 0; i < myVector.size(); i++)
	{
		std::cout << "[" << i << "]" << myVector[i] << std::endl;
	}
	return ;
}

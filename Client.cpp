/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npatron <npatron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 19:36:26 by npatron           #+#    #+#             */
/*   Updated: 2024/07/13 18:22:18 by npatron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include "Channel.hpp"
#include "Logger.hpp"

Client::Client() : _socket(0), _nickname("NULL"), _username("NULL"), _realname("NULL"), _authenticate(false), _pass(false), _user(false), _nick(false)
{
	return ;
}

Client::~Client()
{
	return ;
}

// -------------------GETTERS / SETTERS------------------- //


// SOCKET

void	Client::setSocket(int sock)
{
	this->_socket = sock;
	return ;
}

int	Client::getSocket(void) const
{
	return (this->_socket);
}

// NICKNAME

void Client::setNick(std::string nick)
{
	this->_nickname = nick;
}

std::string Client::getNick(void) const
{
	return (this->_nickname);
}

void Client::setBoolNick(bool var)
{
	this->_nick = var;
}

bool Client::getBoolNick(void) const
{
	return (this->_nick);
}

void Client::setBoolUser(bool var)
{
	this->_user = var;
}

bool Client::getBoolUser(void) const
{
	return (this->_user);
}

void Client::setBoolPass(bool var)
{
	this->_pass = var;
}

bool Client::getBoolPass(void) const
{
	return (this->_pass);
}

bool Client::getBoolAuthenticate(void) const
{
	return (this->_authenticate);
}

void Client::setBoolAuthenticate(bool var)
{
	this->_authenticate = var;
}


// USERNAME

void Client::setUser(std::string user)
{
	this->_username = user;
}

std::string Client::getUser(void) const
{
	return (this->_username);
}

// REALNAME

void Client::setRealName(std::string realname)
{
	this->_realname = realname;
}

std::string Client::getRealName(void) const
{
	return (this->_realname);
}

void	Client::addToChannel(Channel* channel)
{
	_channels.push_back(channel);
}

bool	Client::isInChannel(std::string channel)
{
	for (size_t i = 0; i < _channels.size(); i++)
	{
		if (channel == _channels[i]->getName())
			return (true);
	}
	return (false);
}

void	Client::removeClientChannel(std::string channel)
{
	for (size_t i = 0; i < _channels.size(); i++)
	{
		if (channel == _channels[i]->getName())
		{
			_channels.erase(_channels.begin() + i);
			return ;
		}
	}
	return ;
}


void	Client::sendRPL(std::string base, const char *rpl)
{
	std::string msg = base + " :" + rpl + "\n";
	_logger.logOutput(msg);
	send(_socket, msg.c_str(), msg.size(), 0);	return ;
}

void	Client::printInfos(void)
{
	std::cout << "---------------------------------" << std::endl;
	std::cout << "| Nickname : " << _nickname << std::endl;
	std::cout << "| Username : " << _username << std::endl;
	std::cout << "| Realname : " << _realname << std::endl;
	std::cout << "| Socket : " << _socket << std::endl;
	std::cout << "| Client is in : " << _channels.size() << " channel(s)" << std::endl;
	std::cout << "---------------------------------" << std::endl;
	return ;
}
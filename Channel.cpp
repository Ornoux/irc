/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npatron <npatron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 16:32:59 by npatron           #+#    #+#             */
/*   Updated: 2024/07/13 22:56:24 by npatron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"
#include "Client.hpp"

Channel::Channel() : _thereIsPassword(false), _thereIsTopic(false), _name("NULL"), _password("NULL"), _topic("NULL")
{
	return ;
}

Channel::~Channel()
{
	return ;
}
// NAME
std::string	Channel::getName(void)
{
	return (this->_name);
}

void Channel::setName(std::string name)
{
	this->_name = name;
}

// TOPIC

std::string	Channel::getTopic(void)
{
	return (this->_topic);
}

void Channel::setTopic(std::string topic)
{
	this->_topic = topic;
}

// PASSWORD

std::string	Channel::getPassword(void)
{
	return (this->_password);
}

void Channel::setPassword(std::string password)
{
	this->_password = password;
	_thereIsPassword = true;
}

void	Channel::addClientToChannel(Client *myClient)
{
	_clientsChannel.push_back(myClient);
}

void	Channel::addClientOperatorToChannel(Client *myClient)
{
	_clientsOperators.push_back(myClient);
}

// :irc.example.com 353 Alice = #example :@Bob +Carol Dave

bool	Channel::isClientOperator(std::string user)
{
	for (size_t i = 0; i < _clientsOperators.size(); i++)
	{
		if (user == _clientsOperators[i]->getUser())
			return (true);
	}
	return (false);
}

bool	Channel::isClientInChannel(std::string user)
{
	for (size_t i = 0; i < _clientsChannel.size(); i++)
	{
		if (user == _clientsChannel[i]->getUser())
			return (true);
	}
	return (false);
}

void	Channel::removeClient(std::string user)
{
	for (size_t i = 0; i < _clientsChannel.size(); i++)
	{
		if (user == _clientsChannel[i]->getUser())
		{
			std::cout << "CLIENT TROUVER" << std::endl;
			_clientsChannel.erase(_clientsChannel.begin() + i);
			return ;
		}
	}
	for (size_t i = 0; i < _clientsOperators.size(); i++)
	{
		if (user == _clientsOperators[i]->getUser())
		{
			std::cout << "CLIENT TROUVER OPERA" << std::endl;
			_clientsOperators.erase(_clientsOperators.begin() + i);
			return ;
		}
	}
	return ;
}

void	Channel::sendNotifToClients(std::string id)
{
	int client_socket;
	for (size_t i = 0; i < _clientsChannel.size(); i++)
	{
		client_socket = _clientsChannel[i]->getSocket();
		send(client_socket, id.c_str(), id.size(), 0);
	}
	return ;
}

void	Channel::sendRPL_NAMREPLY(int fd)
{
	std::string list;
	std::string username;
	list = _name + " :";
	std::cout << _clientsChannel.size() << std::endl;
	for (size_t i = 0; i < _clientsChannel.size(); i++)
	{
		username = _clientsChannel[i]->getUser();
		if (isClientOperator(username) == true)
			list += "@" + username + " ";
		else
			list += username + " ";
	}
	list += "\n";
	send(fd, list.c_str(), list.size(), 0);
}

void	Channel::printInfos(void)
{
	std::cout << "---------------------------------" << std::endl;
	std::cout << "| Channel name : " << _name << std::endl;
	std::cout << "| Number of client : " << _clientsChannel.size();
	if (hasPassword() == true)
		std::cout << "| Password : " << _password << std::endl;
	else
		std::cout << "| No password required." << std::endl;
	if (hasTopic() == true)
		std::cout << "| Topic : " << _topic << std::endl;
	else
		std::cout << "| No topic here." << std::endl;
	return ;
}
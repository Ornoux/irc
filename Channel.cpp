/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npatron <npatron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 16:32:59 by npatron           #+#    #+#             */
/*   Updated: 2024/07/12 10:36:05 by npatron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"
#include "Client.hpp"

Channel::Channel() : _name("NULL"), _password("NULL"), _topic("NULL"), _thereIsPassword(false), _thereIsTopic(false)
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
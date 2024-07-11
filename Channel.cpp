/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npatron <npatron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 16:32:59 by npatron           #+#    #+#             */
/*   Updated: 2024/07/11 16:44:03 by npatron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

Channel::Channel()
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

void	Channel::addClientToChannel(Client myClient)
{
	_clientsChannel.push_back(myClient);
}
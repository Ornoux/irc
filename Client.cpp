/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npatron <npatron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 19:36:26 by npatron           #+#    #+#             */
/*   Updated: 2024/07/07 13:48:29 by npatron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

Client::Client() : _socket(0), _nickname("NULL"), _username("NULL"), _realname("NULL")
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


std::ostream& operator<<(std::ostream& o, const Client& rhs)
{
	std::cout << "--------------------------\n";
	std::cout << "NICK : " << rhs.getNick() << std::endl;
	std::cout << "USER : " << rhs.getUser() << std::endl;
	std::cout << "REALNAME : " << rhs.getRealName() << std::endl;
	std::cout << "--------------------------\n";
	return (o);
}
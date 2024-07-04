/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npatron <npatron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 19:36:26 by npatron           #+#    #+#             */
/*   Updated: 2024/07/04 20:10:05 by npatron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

Client::Client() : _socket(0)
{
	return ;
}

Client::~Client()
{
	return ;
}

void	Client::setSocket(int sock)
{
	this->_socket = sock;
	return ;
}

int	Client::getSocket(void)
{
	return (this->_socket);
}
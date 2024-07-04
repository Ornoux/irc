/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npatron <npatron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 13:56:59 by npatron           #+#    #+#             */
/*   Updated: 2024/07/04 19:58:28 by npatron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <iostream>
#include <string>
#include <cstdlib>
#include <unistd.h>

#define BAD_ARGS "To run IRC, you need <port> and <password>, like : ./ircserv <port> <password>\n"
#define INVALID_PORT "Invalid port: Port musts contains 5 digits [0 - 9]\n"
#define PROBLEM_CREATING_SERV "Impossible to create server\n"
class Server
{
	public:
			Server();
			~Server();
			unsigned int getPort();
			void		 setPort(unsigned int port);

			std::string getPassword();
			int			getSocket();
			void		setPassword(std::string password);
			int			create_server(Server& myServer);
			void		close_server(Server& mySever);
	private:
			unsigned int	_port;
			int				_socket;
			std::string		_password;
};

int	valid_port(char *argv);
int	base_parsing(int argc, char **argv);
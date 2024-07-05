/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npatron <npatron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 13:56:59 by npatron           #+#    #+#             */
/*   Updated: 2024/07/06 00:08:23 by npatron          ###   ########.fr       */
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
#include <csignal>
#include "Client.hpp"
#define BAD_ARGS "To run IRC, you need <port> and <password>, like : ./ircserv <port> <password>\n"
#define INVALID_PORT "Invalid port: Port musts contains 5 digits [0 - 9]\n"
#define PROBLEM_CREATING_SERV "Impossible to create server\n"

extern bool _loop;


class Server
{
	public:
			Server();
			~Server();
			unsigned int getPort();
			void		 setPort(unsigned int port);

			std::string getPassword();
			int			getSocket();
			
			void		setPassword(char *pass);
			
			int			create_server(Server& myServer, char **av);
			void		close_server(Server& mySever);
			void		principal_loop(Server& myServer, Client& myClient);
			void		check_signal(void);
			void		accept_client(Server& myServer, Client& myClient);
			
	private:
			unsigned int	_port;
			int				_socket;
			std::string		_password;
};

int	valid_port(char *argv);
int	base_parsing(int argc, char **argv);
void	signal_action(int s);
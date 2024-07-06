/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isouaidi <isouaidi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 19:40:22 by isouaidi          #+#    #+#             */
/*   Updated: 2024/07/06 19:40:23 by isouaidi         ###   ########.fr       */
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
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <csignal>
#include <vector>
#include "Client.hpp"
#define BAD_ARGS "To run IRC, you need <port> and <password>, like : ./ircserv <port> <password>\n"
#define INVALID_PORT "Invalid port: Port musts contains 5 digits [0 - 9]\n"
#define PROBLEM_CREATING_SERV "Impossible to create server\n"
#define BAD_PORT "Port should be between 1 and 65536\n"
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

			std::vector<Client> getVector();
			void		setVector(std::vector<Client> clientList);
			
			void		setPassword(char *pass);
			
			int			create_server(Server& myServer, char **av);
			void		close_server(Server& mySever, std::vector<Client> vectorClient);
			void		principal_loop(Server& myServer, std::vector<Client> vectorClient);
			void		check_signal(void);
			void		accept_client(Server& myServer, std::vector<Client> vectorClient);
			void		is_a_valid_client(Server& myServer, std::vector<Client> vectorClient);
			void		client_valid_pass(Server& myServer, std::vector<Client> vectorClient);
			void		client_valid_nickname(Server& myServer, std::vector<Client> vectorClient);
			void		client_valid_userline(Server& myServer, std::vector<Client> vectorClient);
			void		client_valid_realname(Server& myServer, std::vector<Client> vectorClient);
			
	private:
			unsigned int	_port;
			int				_socket;
			std::string		_password;
			std::vector<Client> _clientList;
			int				_clientsConnected;
};

// UTILS

int	valid_port(char *argv);
int	base_parsing(int argc, char **argv);
void	signal_action(int s);
int	int_max(char *str);


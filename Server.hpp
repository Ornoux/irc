/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npatron <npatron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 13:56:59 by npatron           #+#    #+#             */
/*   Updated: 2024/07/08 10:15:35 by npatron          ###   ########.fr       */
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
#include <map>
#include <iterator>
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
			void		setSocket(int sock);
			
			
			void		setPassword(char *pass);
			
			int			create_server(Server& myServer, char **av);
			void		close_server();
			void		principal_loop(Client& myClient);
			void		check_signal(void);
			void		accept_client(Client& myClient);
			void		is_a_valid_client(Client& myClient);
			void		client_valid_pass(Client& myClient);
			void		client_valid_nickname(Client& myClient);
			void		client_valid_userline(Client& myClient);
			void		client_valid_realname(Client& myClient);

			void		disconnect_clients_from_serv();

			void		print_client_map();
			void		check_clients_here();
			
	private:
			unsigned int	_port;
			int				_socket;
			std::string		_password;
			std::map<int, Client> _clientList;
			int				_nbClients;
};

// UTILS

int	valid_port(char *argv);
int	base_parsing(int argc, char **argv);
void	signal_action(int s);

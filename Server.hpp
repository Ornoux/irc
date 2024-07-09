/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npatron <npatron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 13:56:59 by npatron           #+#    #+#             */
/*   Updated: 2024/07/09 18:18:13 by npatron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <iostream>
#include <poll.h>
#include <string>
#include <cstring>
#include <fcntl.h>
#include <cstdlib>
#include <unistd.h>
#include <csignal>
#include <vector>
#include <iterator>
#include "Client.hpp"
#include "Exceptions.hpp"

#define BAD_ARGS "To run IRC, you need <port> and <password>, like : ./ircserv <port> <password>\n"
#define INVALID_PORT "Invalid port: Port musts contains 5 digits [0 - 9]\n"
#define PROBLEM_CREATING_SERV "Impossible to create server\n"

class Server
{
	public:
			Server();
			~Server();

			// SETTERS && GETTERS

			unsigned int getPort();
			void		 setPort(unsigned int port);

			std::string getPassword();
			
			int			getSocket();
			void		setSocket(int sock);
				
			void		setPassword(char *pass);
			
			// MEMBER FUNCTIONS
			
			void		loop_test(char **av, Client myClient);
			void		launch_serv(char **av);
			void		AddClientToVector(Client myClient);
			void		DeleteClientFromServ(int i);
			void		check_signal(void);
			void		check_clients_here();
			bool		isClientDisconnected(int fd);
			void		SendDataToClient(int fd, std::string msg);
			void		printClient(void);

	private:
			unsigned int	_port;
			int				_socket;
			std::string		_password;
			std::vector<Client>	_clientVector;
			int				_nbClients;
};

// UTILS

int		valid_port(char *argv);
void	base_parsing(int argc, char **argv);
void	signal_action(int s);
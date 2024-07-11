/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isouaidi <isouaidi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 13:56:59 by npatron           #+#    #+#             */
/*   Updated: 2024/07/11 15:59:43 by isouaidi         ###   ########.fr       */
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

#define ERR_NEEDMOREPARAMS "Not enough parameters\n"
#define ERR_ALREADYREGISTRED "Unauthorized command (already registered)\n"
#define ERR_NONICKNAMEGIVEN "No nickname given\n"
#define ERR_ERRONEUSNICKNAME "Erroneous nickname\n"


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
			
			void		loop(char **av, Client myClient);
			void		launch_serv(char **av);
			void		AddClientToVector(Client myClient);
			void		DeleteClientFromServ(int i);
			void		check_signal(void);
			void		check_clients_here();
			bool		isClientDisconnected(int fd);
			void		getCmd(int fd, std::string cmd);
			void		treatVectorCmd(int fd, std::vector<std::string> vectorCmd);
			void		printClient(void);
			void		isAuthenticate(Client myClient);
			int			findClientByFd(int fd);
			// CMD

			void		checkPass(int fd, std::string cmd);
			void		checkNick(int fd, std::string cmd);
			void		checkUser(int fd, std::string cmd);
			void		getNick(int fd, std::string cmd);
			
			void		client_valid_realname(Client& myClient);
			void		client_valid_nickname(Client& myClient);
			void		client_valid_pass(Client& myClient);
			void		client_valid_username(Client& myClient);

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
int		int_max(char *str);
bool	checkSpace(char c, const char *str);
bool	checkNormeCara(const char *str);




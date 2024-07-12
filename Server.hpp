/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npatron <npatron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 13:56:59 by npatron           #+#    #+#             */
/*   Updated: 2024/07/12 13:21:51 by npatron          ###   ########.fr       */
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
#include <ctime>
#include <fstream>

#include "Logger.hpp"
#include "Channel.hpp"
#include "Client.hpp"
#include "Exceptions.hpp"

// UTILS CMD
#define ERR_NEEDMOREPARAMS "Not enough parameters\n"

// PASS
#define ERR_ALREADYREGISTRED "Unauthorized command (already registered)\n"

// JOIN
#define ERR_BADCHANMASK "Bad Channel Mask\n"
#define ERR_USERONCHANNEL "is already on channel\n"
#define ERR_BADCHANNELKEY "Cannot join channel\n"
#define ERR_KEYSET "Channel key already set\n"
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
			
			void		loop(char **av, Client* myClient);
			void		launch_serv(char **av);
			void		AddClientToVector(Client* myClient);
			void		DeleteClientFromServ(int i);
			void		check_signal(void);
			void		check_clients_here();
			bool		isClientDisconnected(int fd);
			void		getCmd(int fd, std::string cmd);
			void		treatVectorCmd(int fd, std::vector<std::string> vectorCmd);
			void		printClient(void);
			void		isAuthenticate(Client *myClient);
			Client*		findClientByFd(int fd);
			Channel*	findChannelByName(std::string name);
			
			// CMD AUTH

			void		checkPass(int fd, std::string cmd);
			void		checkNick(int fd, std::string cmd);
			void		checkUser(int fd, std::string cmd);
			void		getNick(int fd, std::string cmd);

			// CMD CHANNELS

			void							handleChannels(int fd, std::string cmd);
			bool							channelNameIsAcceptable(std::string cmd);
			bool							channelNameIsFree(std::string cmd);
			std::vector<std::string>		splitCmdNameChannels(std::string cmd);
			std::vector<std::string>		splitCmdPasswordChannels(std::string cmd);
			bool							channelAlreadyExists(std::string cmd);
			


	private:
			unsigned int	_port;
			int				_socket;
			std::string		_password;
			std::vector<Client*>	_clientVector;
			std::vector<Channel*> _channelVector;
			int				_nbClients;
			Logger			_logger;
};

// UTILS

bool	charAcceptableNameChannel(char c);
int		valid_port(char *argv);
void	base_parsing(int argc, char **argv);
void	signal_action(int s);
int		int_max(char *str);
bool	checkSpace(char c, const char *str);
bool	checkNormeCara(const char *str);




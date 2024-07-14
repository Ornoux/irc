/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isouaidi <isouaidi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 13:56:59 by npatron           #+#    #+#             */
/*   Updated: 2024/07/14 20:33:36 by isouaidi         ###   ########.fr       */
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
#define ERR_NEEDMOREPARAMS "Not enough parameters"

// PASS
#define ERR_ALREADYREGISTRED "Unauthorized command (already registered)"

// JOIN
#define ERR_BADCHANMASK "Bad Channel Mask"
#define ERR_USERONCHANNEL "is already on channel"
#define ERR_BADCHANNELKEY "Cannot join channel"
#define ERR_KEYSET "Channel key already set"
#define RPL_NOTOPIC "No topic is set"
#define RPL_ENDOFNAMES "End of NAMES list"

//NICK
#define ERR_NONICKNAMEGIVEN "No nickname given"
#define ERR_ERRONEUSNICKNAME "Erroneous nickname"
#define ERR_NICKNAMEINUSE "Nickname is already in use"

//KICK
#define ERR_CHANOPRIVSNEEDED "You're not channel operator"
#define ERR_NOSUCHCHANNEL "No such channel"
#define ERR_USERNOTINCHANNEL "They aren't on that channel"
#define ERR_NOTONCHANNEL "You're not on that channel"

//INVITE
#define ERR_NOSUCKNICK "No such nick/channel"

class Server
{
	public:
			Server();
			~Server();

			// SETTERS && GETTERS

			unsigned int 					getPort();
			void		 					setPort(unsigned int port);
			int								getSocket();
			void							setSocket(int sock);			
			void							setPassword(char *pass);
			std::string 					getPassword();
			
			// MEMBER FUNCTIONS
			
			void							loop(char **av);
			void							launch_serv(char **av);
			void							DeleteClientFromServ(int i);
			void							check_signal(void);
			void							check_clients_here();
			bool							isClientDisconnected(int fd);
			void							getCmd(int fd, std::string cmd);
			void							treatVectorCmd(int fd, std::vector<std::string> vectorCmd);
			void							printClient(void);
			void							isAuthenticate(Client *myClient);
			Client*							AddClientToVector();
			Client*							findClientByFd(int fd);
			Client*							findClientByUser(std::string user);
			Channel*						findChannelByName(std::string name);
			
			// CMD AUTH

			std::string 					stockCtrl(std::string msg);
			bool							similarNick(const char *nick);
			void							checkPass(int fd, std::string cmd);
			void							checkNick(int fd, std::string cmd);
			void							checkUser(int fd, std::string cmd);
			void							getNick(int fd, std::string cmd);
			void							cmdKick(int fd, std::string cmd, std::vector<std::string> vectorSplit);
			void							cmdTopic(int fd,std::vector<std::string> vectorSplit);
			void							cmdInvite(int fd, std::vector<std::string> vectorSplit);

			// CMD CHANNELS

			void							handleChannels(int fd, std::string cmd, std::vector<std::string> vectorSplit);
			void							sendNotifTopicToClients(int fd_sender, Channel* myChannel);
			bool							channelNameIsAcceptable(std::string cmd);
			bool							channelNameIsFree(std::string cmd);
			bool							channelAlreadyExists(std::string cmd);
			bool							isClientExisting(std::string user);
			std::vector<std::string>		splitCmdNameChannels(std::string cmd);
			std::vector<std::string>		splitCmdPasswordChannels(std::string cmd);
			std::vector<std::string>		splitString(std::string cmd, std::string delimiter);
	
	private:
			unsigned int					_port;
			int								_socket;
			int								_nbClients;
			std::string						_password;
			Logger							_logger;
			std::vector<Client*>			_clientVector;
			std::vector<Channel*> 			_channelVector;
			std::string 					_ctrl;
};

// UTILS

bool	charAcceptableNameChannel(char c);
int		valid_port(char *argv);
void	base_parsing(int argc, char **argv);
void	signal_action(int s);
int		int_max(char *str);
bool	checkSpace(char c, const char *str);
bool	checkNormeCara(const char *str);
void	printStringVector(std::vector<std::string> myVector);



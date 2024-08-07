/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npatron <npatron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 19:36:29 by npatron           #+#    #+#             */
/*   Updated: 2024/07/16 17:56:01 by npatron          ###   ########.fr       */
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
#include "Logger.hpp"
class Channel;

class Client
{
	public:
			Client();
			~Client();
			
			int	getSocket(void) const;
			void setSocket(int sock);
			
			std::string getNick(void) const;
			void		setNick(std::string nick);

			std::string getRealName(void) const;
			void		setRealName(std::string nick);

			std::string getUser(void) const;
			void		setUser(std::string nick);

			void		setBoolPass(bool var);
			bool		getBoolPass(void) const;

			void		setBoolNick(bool var);
			bool		getBoolNick(void) const;
		
			void		setBoolUser(bool var);
			bool		getBoolUser(void) const;

			bool		getBoolAuthenticate(void) const;
			void		setBoolAuthenticate(bool var);
			
			bool		isInChannel(std::string channel);
			void		addToChannel(Channel *channel);
			void		removeClientChannel(std::string client);
			void		sendRPL(std::string base, const char *error_msg);
			void		printInfos(void);
			void		addInvitation(Channel* _channel) {_channelsInvited.push_back(_channel);}
			bool		isInvitedToChannel(std::string channelName);
			std::string	setHistoric(std::string msg);

	private:
			int			_socket;
			std::string	_nickname;
			std::string	_username;
			std::string	_realname;
			
			std::vector<Channel*> _channels;
			std::vector<Channel*> _channelsInvited;
			bool		_authenticate;
			bool		_pass;
			bool		_user;
			bool		_nick;
			
			std::string	_historic;
			
			Logger		_logger;
};

std::ostream& operator<<(std::ostream& o, const Client& rhs);
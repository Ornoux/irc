/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npatron <npatron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 16:13:03 by npatron           #+#    #+#             */
/*   Updated: 2024/07/16 11:00:31 by npatron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <vector>

class Client;

class Channel
{
	public:
			Channel();
			~Channel();
		
			std::string getPassword(void);
			std::string getTopic(void);
			std::string getName(void);
			size_t		getSizeChannel(void) {return (_clientsChannel.size());}
			size_t		getSizeChannelOperators(void) {return (_clientsOperators.size());}
			bool		getIsInviteOnly(void) {return _isInviteOnly;}
			void		setIsInviteOnly(bool invite) {_isInviteOnly = invite;}
			bool		getIsTopicRestricted(void) {return _isTopicRestricted;}
			void		setIsTopicRestricted(bool topicrestricted) {_isTopicRestricted = topicrestricted;}
			bool		getIsLimitedNumberClients(void) {return _isLimitedNumberClients;}
			void		setIsLimitedNumberClients(bool limit) {_isLimitedNumberClients = limit;}
			void		setName(std::string name);
			void		setThereIsPassword(bool	password) {_thereIsPassword = password;}
			void		setPassword(std::string name);
			void		setTopic(std::string name);
			void		setBoolTopic(bool topic) {_thereIsTopic = topic;}
			void		sendNotifToClients(std::string id);

			void		setLimitNumberClient(size_t nb) {_nbLimitUsers = nb;}
			size_t		getLimitNumberClient(void) {return (_nbLimitUsers);}
			bool		hasPassword(void) {return _thereIsPassword;}
			bool		hasLimit(void) {return _isLimitedNumberClients;}
			bool		hasTopic(void) {return _thereIsTopic;}
			bool		channelAlreadyExists(std::string name);

			
				
			void		addClientToChannel(Client* myClient);
			void		addClientOperatorToChannel(Client* myClient);
			void		removeClientOperator(std::string user);
			void		printInfos(void);
			void		sendRPL_NAMREPLY(int fd);
			bool		isClientOperator(std::string user);
			bool		isClientInChannel(std::string user);
			void		removeClient(std::string user);
	private: 
			
			
			bool		_thereIsPassword;
			bool		_thereIsTopic;

			bool		_isInviteOnly;
			bool		_isTopicRestricted;
			bool		_isLimitedNumberClients;
			size_t		_nbLimitUsers;
			
			std::string _name;
			std::string _password;
			std::string _topic;
			std::vector<Client*> _clientsChannel;
			std::vector<Client*> _clientsOperators;
};
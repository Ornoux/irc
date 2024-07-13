/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npatron <npatron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 16:13:03 by npatron           #+#    #+#             */
/*   Updated: 2024/07/13 18:40:53 by npatron          ###   ########.fr       */
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
			void		setName(std::string name);
			void		setPassword(std::string name);
			void		setTopic(std::string name);
			
			bool		hasPassword(void) {return _thereIsPassword;}
			bool		hasTopic(void) {return _thereIsTopic;}
			bool		channelAlreadyExists(std::string name);
				
			void		addClientToChannel(Client* myClient);
			void		addClientOperatorToChannel(Client* myClient);
			void		printInfos(void);
			void		sendRPL_NAMREPLY(int fd);
			bool		isClientOperator(std::string user);
			bool		isClientInChannel(std::string user);
			void		removeClient(std::string user);
	private: 
			
			
			bool		_thereIsPassword;
			bool		_thereIsTopic;
			std::string _name;
			std::string _password;
			std::string _topic;
			std::vector<Client*> _clientsChannel;
			std::vector<Client*> _clientsOperators;
};
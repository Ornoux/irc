/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npatron <npatron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 16:13:03 by npatron           #+#    #+#             */
/*   Updated: 2024/07/12 16:33:31 by npatron          ###   ########.fr       */
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
			void		setName(std::string name);
			void		setPassword(std::string name);
			void		setTopic(std::string name);
			
			bool		hasPassword(void) {return _thereIsPassword;}
			bool		hasTopic(void) {return _thereIsTopic;}
			bool		channelAlreadyExists(std::string name);
				
			void		addClientToChannel(Client* myClient);
			void		addClientOperatorToChannel(Client* myClient);
			void		printInfos(void);
	private: 
			
			
			bool		_thereIsPassword;
			bool		_thereIsTopic;
			std::string _name;
			std::string _password;
			std::string _topic;
			std::vector<Client*> _clientsChannel;
			std::vector<Client*> _clientsOperators;
};
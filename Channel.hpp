/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npatron <npatron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 16:13:03 by npatron           #+#    #+#             */
/*   Updated: 2024/07/12 10:31:12 by npatron          ###   ########.fr       */
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

			void		setName(std::string name);
			std::string getName(void);
			
			void		setPassword(std::string name);
			std::string getPassword(void);

			void		setTopic(std::string name);
			std::string getTopic(void);
			
			bool		hasPassword(void) {return _thereIsPassword;}
			bool		hasTopic(void) {return _thereIsTopic;}
			bool		channelAlreadyExists(std::string name);
			
			void		addClientToChannel(Client* myClient);
			void		addClientOperatorToChannel(Client* myClient);

			void		printInfos(void);
	private: 
			std::string _name;
			std::string _password;
			std::string _topic;
			
			bool		_thereIsPassword;
			bool		_thereIsTopic;
			
			std::vector<Client*> _clientsChannel;
			std::vector<Client*> _clientsOperators;
};
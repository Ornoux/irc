/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npatron <npatron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 16:13:03 by npatron           #+#    #+#             */
/*   Updated: 2024/07/11 17:15:17 by npatron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <vector>
#include "Client.hpp"

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
			bool		channelAlreadyExists(std::string name);
			
			void		addClientToChannel(Client myClient);
	private: 
			std::string _name;
			std::string _password;
			std::string _topic;
			
			bool		_thereIsPassword;
			
			std::vector<Client> _clientsChannel;
			std::vector<Client> _clientsOperators;
};
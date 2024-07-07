/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npatron <npatron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 19:36:29 by npatron           #+#    #+#             */
/*   Updated: 2024/07/07 13:48:09 by npatron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <iostream>

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

	private:
			int		_socket;
			std::string	_nickname;
			std::string	_username;
			std::string	_realname;
};

std::ostream& operator<<(std::ostream& o, const Client& rhs);
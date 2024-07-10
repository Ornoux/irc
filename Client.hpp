/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npatron <npatron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 19:36:29 by npatron           #+#    #+#             */
/*   Updated: 2024/07/10 20:31:06 by npatron          ###   ########.fr       */
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

			void		setBoolPass(bool var);
			bool		getBoolPass(void) const;

			void		setBoolNick(bool var);
			bool		getBoolNick(void) const;
		
			void		setBoolUser(bool var);
			bool		getBoolUser(void) const;

			bool		getBoolAuthenticate(void) const;
			void		setBoolAuthenticate(bool var);
			

	private:
			int			_socket;
			std::string	_nickname;
			std::string	_username;
			std::string	_realname;
			
			bool		_authenticate;
			bool		_pass;
			bool		_user;
			bool		_nick;
};

std::ostream& operator<<(std::ostream& o, const Client& rhs);
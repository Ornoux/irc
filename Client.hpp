/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npatron <npatron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 19:36:29 by npatron           #+#    #+#             */
/*   Updated: 2024/07/06 00:07:27 by npatron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

class Client
{
	public:
			Client();
			~Client();
			
			int	getSocket(void);
			void setSocket(int sock);

	private:
			int		_socket;
	
};
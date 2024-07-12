/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Exceptions.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npatron <npatron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 18:15:53 by npatron           #+#    #+#             */
/*   Updated: 2024/07/11 22:42:16 by npatron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <exception>


class BadArgs : public std::exception
{
    public:
            const char* what() const throw()
            {
                return ("To run IRC, you need <port> and <password>, like : ./ircserv <port> <password>");
            }
};

class BadPort : public std::exception
{
    public:
            const char* what() const throw()
            {
                return ("Invalid port: Port musts be '6661' | '6662' | '6663' | '6664' | '6665' | '6666' | '6667' | '6668' | '6669' ");
            }
};

class CreationServer : public std::exception
{
    public:
            const char* what() const throw()
            {
                return ("Impossible to create server");
            }
};

class AcceptError : public std::exception
{
    public:
            const char* what() const throw()
            {
                return ("Accept error");
            }
};

class SelectError : public std::exception
{
    public:
            const char* what() const throw()
            {
                return ("Select error");
            }
};

class FindClient : public std::exception
{
    public:
            const char* what() const throw()
            {
                return ("Error during search of client");
            }
};

class FindChannel : public std::exception
{
    public:
            const char* what() const throw()
            {
                return ("Error during search of channel");
            }
};
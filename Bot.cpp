/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npatron <npatron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:55:38 by npatron           #+#    #+#             */
/*   Updated: 2024/07/16 15:57:12 by npatron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int connect_to_server(const char* address, int port)
{
    int fd;
    struct sockaddr_in server_addr;

    fd = socket(AF_INET, SOCK_STREAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
	connect(fd, (struct sockaddr*)&server_addr, sizeof(server_addr));
    return (fd);
}

int main(int argc, char* argv[])
{
	int fd_server;
    if (argc != 3)
	{
        std::cout << "Usage: " << argv[0] << " <adress> <port>" << std::endl;
        return (1);
    }

    const char* address = argv[1];
    int port = atoi(argv[2]); 

    fd_server = connect_to_server(address, port);
	send(fd_server, "BOT\r", 5, 0);
	//close(fd_server);
    return 0;
}
		
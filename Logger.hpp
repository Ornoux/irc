#pragma once

#include <iostream>
#include <string>
#include <ctime>

#define GRAS  "\033[1m"

// Codes ANSI pour les couleurs
#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"

class Logger
{
    public:
            Logger() {}
            ~Logger() {}

            void logError(const std::string& message) {
                std::cout << RED << "[ERROR] " << message << RESET << std::endl;
            }

            void logInfo(const std::string& message) {
                std::string timestamp = getCurrentTime();
                std::cout << BLUE << "[INFO] " << timestamp << " : " << message << RESET << std::endl;
            }

            void logInput(const std::string& message) {
                std::cout << CYAN << "[INPUT] " << message << RESET << std::endl;
            }
            void logPriv(const std::string& nick, const std::string& toUser, const std::string& message) {
                std::cout << RED << GRAS << "[PRIVMSG] " << nick <<" Send to "<< toUser << " --> " << message << RESET << std::endl;
            }
            void logAccept(const std::string& message) {
                std::cout << GRAS << MAGENTA << "[" << message << "] Accepted\n"<< RESET << std::endl;
            }

            void logOutput(const std::string& message) {
                std::cout << GREEN << "[OUTPUT] " << message << RESET << std::endl;
            }

            std::string getCurrentTime()
            {
                std::time_t now = std::time(NULL);
                char buf[100];
                std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
                return std::string(buf);
            }
};
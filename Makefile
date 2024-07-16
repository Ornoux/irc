# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: npatron <npatron@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/03 16:53:15 by npatron           #+#    #+#              #
#    Updated: 2024/07/16 15:57:05 by npatron          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =  main.cpp Client.cpp Server.cpp Utils.cpp Channel.cpp \
					
OBJS = $(SRCS:.cpp=.o)

NAME = ircserv
CC = c++
CFLAGS = -Wall -Wextra -g -Werror -std=c++98
RM = rm -rf

RESET = \033[0m
GRAS = \033[1m
ITALIQUE = \033[3m
SOULIGN = \033[4m
UP = \033[A
BLINK = \033[6m

YEL = \033[38;5;220m
ORANGE = \033[38;5;216m
BLEU =  \033[38;5;27m 
DARKBLUE = \033[38;5;21m
RED = \033[38;5;130m
RED1 = \033[38;5;196m
GREEN1 =\033[38;5;46m
GREEN = \033[38;5;85m

FICH_COUNT = 0
NBR_TOT_FICHIER = 5
NBR_COMPILER = ${shell expr 100 \* ${FICH_COUNT} / ${NBR_TOT_FICHIER}}
BAR =  ${shell expr 23 \* ${FICH_COUNT} / ${NBR_TOT_FICHIER}}


${MAIN_PATH}%.o:%.cpp 
	@${eval FICH_COUNT = ${shell expr ${FICH_COUNT} + 1}}
	@${CC} ${CFLAGS} -c -I . $< -o ${<:.cpp=.o} 
	@echo ""
	@echo " ${GRAS}${RED1}-> COMPILATION EN COURS${RESET}${GRAS}${YEL}[IRC]${RESET}"
	@printf " ${RED1}${GRAS}[${YEL}%-23.${BAR}s${RED1}] [%d/%d (%d%%)]${RESET}" "-----------------------" ${FICH_COUNT} ${NBR_TOT_FICHIER} ${NBR_COMPILER}
	@echo "${UP}${UP}${UP}"

all : ${NAME}


${NAME}: ${OBJS}
	@${CC} ${CFLAGS} ${OBJS} -o ${NAME} 
	@echo "\n\n\n ${GRAS}${RED1}IRC EST COMPILÉ 👏${RESET}\n"
	
clean:
	@${RM}  ${OBJS} 
	@echo "${GREEN1}${GRAS}\tNETTOYAGE 🛁${RESET}"
	@echo "${BLEU}${ITALIQUE} -les fichiers sont supprimés${RESET}"

fclean: clean
	@${RM} ${NAME}
	@echo "${BLEU}${ITALIQUE} -${NAME} est supprimê${RESET}"

re: fclean all

.PHONY: all clean fclean re

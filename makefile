# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: corosteg <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/10/02 13:49:12 by corosteg          #+#    #+#              #
#    Updated: 2017/10/17 15:53:32 by corosteg         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
LIB_PATH = ./libft/
LIB = $(LIB_PATH)libft.a
FLAGS = -Wall -Werror -Wextra
SRCS = ./srcs/main.c\
	   ./srcs/check_funct.c\
	   ./srcs/ft_cd.c\
	   ./srcs/ft_env.c\
	   ./srcs/ft_echo.c\
	   ./srcs/ft_exit.c\
	   ./srcs/ft_setenv.c\
	   ./srcs/ft_unsetenv.c\
	   ./srcs/check_funct2.c\
	   ./srcs/main2.c\
	   ./srcs/ft_cd2.c

all: $(NAME)

$(NAME):
		@echo "\033[31m" "compiling" [ $(NAME) ]
		make -C $(LIB_PATH)
		gcc $(FLAGS) $(SRCS) $(LIB) -o $(NAME)
		@echo "\033[32m" "    -------- minishell has been Created --------"

cc:
		gcc $(SRCS) $(LIB) -o $(NAME)

clean:
		@echo "\033[34m" "Deleting"
		make -C $(LIB_PATH) clean

fclean:
		@echo "\033[34m" "Deleting"
		/bin/rm -f $(NAME)
		make -C $(LIB_PATH) fclean

re: fclean all

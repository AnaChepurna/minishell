# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: achepurn <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/03/21 21:48:41 by achepurn          #+#    #+#              #
#    Updated: 2018/03/21 21:48:44 by achepurn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAG = -Wall -Wextra -Werror -g
NAME = minishell
SRC = 	main.c \
		output.c \
		execute.c \
		env.c \
		cd.c \
		input.c \
		signal.c \
		garland.c \
		env2.c \
		utils.c \
		terminal.c \
		memcommand.c \
		memcommand2.c \
		parse.c \
		overlap.c \
		overlap2.c \
		control.c \
		autocomplete.c
OBJ = $(SRC:.c=.o)
LIB = libft/libft.a

all: $(NAME)

$(NAME): $(LIB) $(OBJ)
	$(CC) $(OBJ) libft/libft.a -o $(NAME)

%.o: %.c
	$(CC) -c $(CFLAG) $<

clean:
	rm -rf $(OBJ)
	make -C libft/ clean

fclean: clean
	rm -rf $(NAME)
	make -C libft/ fclean

$(LIB):
	make -C libft

re: fclean all

CC = gcc
CFLAG = -Wall -Wextra -Werror
NAME = minishell
SRC = 	main.c \
		output.c \
		execute.c \
		env.c \
		cd.c \
		input.c \
		signal.c \
		garland.c \
		env2.c
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

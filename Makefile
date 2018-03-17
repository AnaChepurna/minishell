SRC = 	main.c \
		output.c \
		execute.c \
		env.c \
		cd.c \
		input.c \
		signal.c
LIB = libft/libft.a

all:
	gcc -Wall -Wextra -Werror $(SRC) $(LIB)
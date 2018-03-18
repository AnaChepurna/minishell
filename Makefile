SRC = 	main.c \
		output.c \
		execute.c \
		env.c \
		cd.c \
		input.c \
		signal.c \
		garland.c
LIB = libft/libft.a

all:
	gcc -g -Wall -Wextra -Werror $(SRC) $(LIB)
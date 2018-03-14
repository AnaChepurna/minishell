SRC = 	main.c \
		utils.c \
		execute.c
LIB = libft/libft.a

all:
	gcc -Wall -Wextra -Werror $(SRC) $(LIB)
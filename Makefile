SRC = 	main.c \
		echo.c \
		execute.c \
		env_manipulate.c
LIB = libft/libft.a

all:
	gcc -Wall -Wextra -Werror $(SRC) $(LIB)
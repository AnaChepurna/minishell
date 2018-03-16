SRC = 	main.c \
		echo.c \
		execute.c \
		env.c \
		cd.c \
		bonus.c
LIB = libft/libft.a

all:
	gcc -Wall -Wextra -Werror $(SRC) $(LIB)
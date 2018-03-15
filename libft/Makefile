# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: achepurn <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/19 16:42:13 by achepurn          #+#    #+#              #
#    Updated: 2017/11/25 22:18:50 by achepurn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror
INCL = ./
SRC = src/
OBJ = obj/
FILES = ft_lstprint.c ft_striter.c ft_lstrm.c ft_striteri.c \
	  ft_arrtolst.c ft_memalloc.c ft_strjoin.c ft_atoi.c \
	  ft_memccpy.c ft_strlcat.c ft_atoi_base.c ft_memchr.c \
	  ft_strlen.c ft_atoll.c ft_memcmp.c ft_strmap.c ft_bzero.c \
	  ft_memcpy.c ft_strmapi.c ft_isalnum.c	ft_memdel.c ft_strncat.c \
	  ft_isalpha.c ft_memmove.c ft_strncmp.c ft_isascii.c ft_memset.c \
	  ft_strncpy.c ft_isdigit.c ft_putchar.c ft_strnequ.c ft_isprint.c \
	  ft_putchar_fd.c ft_strnew.c ft_itoa.c ft_putendl.c ft_strnstr.c \
	  ft_itoa_base.c ft_putendl_fd.c ft_strrchr.c ft_lstadd.c ft_putnbr.c \
	  ft_lstaddend.c ft_putnbr_fd.c ft_arrfree.c ft_lsttoarr.c \
	  ft_lstaddindex.c ft_putstr.c ft_strsplit.c ft_lstdel.c ft_putstr_fd.c \
	  ft_strsplitlst.c ft_lstdelone.c ft_strcat.c ft_strstr.c \
	  ft_lstget.c ft_strchr.c ft_strsub.c ft_lstgetindex.c ft_strclr.c \
	  ft_strtrim.c ft_lstiter.c ft_strcmp.c ft_tolower.c ft_lstlen.c \
	  ft_strcpy.c ft_toupper.c ft_lstmap.c ft_strdel.c ft_wstrlen.c \
	  ft_lstnew.c ft_strdup.c ft_lstpop.c ft_strequ.c ft_swap.c \
	  ft_strsort.c  ft_arrlen.c ft_arrrev.c ft_memclr.c ft_strrev.c \
	  get_next_line.c ft_strsplitm.c ft_strsplitmq.c ft_pathjoin.c
O_FILES = $(addprefix $(OBJ), $(FILES:.c=.o))

all: $(NAME)

$(NAME): $(OBJ) $(O_FILES)
	ar rc $(NAME) $(O_FILES)
	ranlib $(NAME)

$(OBJ):
	mkdir -p $@

$(OBJ)%.o: $(SRC)%.c
	$(CC) -c $(CFLAGS) -I $(INCL) $< -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -f $(NAME)
	rm -f libft.h.gch

re: fclean all

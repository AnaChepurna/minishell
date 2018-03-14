#ifndef MINISHELL_H
#define MINISHELL_H

# include "libft/libft.h"
# include <stdio.h>

# define MAGENTA	"\x1B[35m"
# define RESET		"\x1B[0m"

t_list	*g_env;

/*
**execute.c
*/
void	execute(char *command);

/*
**utils.c
*/
void	print_prompt(void);
void	print_error_arg(char *arg);
int		print_env(void);
void	exit_minishell(void);

#endif
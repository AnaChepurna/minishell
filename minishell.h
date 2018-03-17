#ifndef MINISHELL_H
#define MINISHELL_H

# include "libft/libft.h"
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>

# define MAGENTA	"\x1B[35m"
# define RESET		"\x1B[0m"

t_list	*g_env;
t_list	*g_undo;
char	**g_start_env;

/*
**execute.c
*/
void	execute(char *command);

/*
**output.c
*/
void	print_prompt(void);
void	print_error(char *arg, char *msg);
int		echo(char **args);
int		print_env(void);

/*
**main.c
*/
void	clear_global(void);
void	init_global(void);

/*
**env.c
*/
char	*get_var(char *var_name);
int		set_var(char *var_name, char *value, int save);
int		unset_var(char *var_name, int save);
int		undo_var(char *var_name);
int		reset_env(void);

/*
**cd.c
*/
int		cd(char **args);

/*
**input.c
*/
char	*get_input(void);

#endif
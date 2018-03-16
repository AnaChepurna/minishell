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

/*
**execute.c
*/
void	execute(char *command);

/*
**utils.c
*/
void	print_prompt(void);
void	print_error(char *arg, char *msg);
int		echo(char **args);
int		print_env(void);

/*
**main.c
*/
void	exit_minishell(void);

/*
**env.c
*/
char	*get_var(char *var_name);
void	set_var(char *var_name, char *value);
void	unset_var(char *var_name);
int		ft_setenv(char **args);
int		ft_unsetenv(char **args);

/*
**cd.c
*/
int		cd(char **args);

/*
**undo.c
*/
int		undoenv(char **args);

#endif
#ifndef MINISHELL_H
#define MINISHELL_H

# include "libft/libft.h"
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>

# define RED		"\x1B[31m"
# define GREEN		"\x1B[32m"
# define YELLOW		"\x1B[33m"
# define BLUE		"\x1B[34m"
# define MAGENTA	"\x1B[35m"
# define CYAN		"\x1B[36m"
# define WHITE		"\x1B[37m"
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
void	debug_specials(char **input);
void	delete_quotes(char **input);

/*
**signal.c
*/
void	sigint_handler(int signo);
void	sigint_fork_handler(int signo);

/*
**garland.c
*/
char	*get_color(void);

#endif
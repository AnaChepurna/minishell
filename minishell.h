/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achepurn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 21:47:56 by achepurn          #+#    #+#             */
/*   Updated: 2018/03/21 21:47:58 by achepurn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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
int		g_status;
int		g_ret_status;

/*
**execute.c
*/
void	execute(char *command);
int		is_bin(char *path, int	check_dir);
int		run(char *path, char **args, t_list *local_env);
int		exec_bin(char **args, t_list *env);

/*
**output.c
*/
void	print_prompt(void);
void	print_error(char *arg, char *msg);
int		echo(char **args);

/*
**main.c
*/
void	clear_global(void);
void	init_global(void);
int		exit_minishell(char **args);

/*
**env.c
*/
char	*get_var(t_list *env, char *var_name);
int		set_var(char *var_name, char *value, int save);
int		unset_var(char *var_name, int save);
int		undo_var(char *var_name);
int		reset_env(void);

/*
**cd.c
*/
int		cd(char **args);
void	set_pwd(char *path, char *oldpwd, int p);
void	format_path(char **pwd);

/*
**input.c
*/
char	*get_input(void);
void	debug_home(char **input);
void	debug_eof(char	**input);

/*
**signal.c
*/
void	sigint_handler(int signo);
void	sigint_fork_handler(int signo);

/*
**garland.c
*/
char	*get_color(void);

/*
**env2.c
*/
int		env(char **args);
void	print_list_content(t_list *lst);

void		debug_vars(char	**input);

#endif

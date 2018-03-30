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
# include <termios.h>
# include <dirent.h>
# include <sys/ioctl.h>

# include <stdio.h>

# define RED		"\x1B[31m"
# define GREEN		"\x1B[32m"
# define YELLOW		"\x1B[33m"
# define BLUE		"\x1B[34m"
# define MAGENTA	"\x1B[35m"
# define CYAN		"\x1B[36m"
# define WHITE		"\x1B[37m"
# define RESET		"\x1B[0m"
# define UP 1
# define DOWN 2
# define ADD 3

t_list	*g_env;
t_list	*g_undo;
char	**g_start_env;
int		g_status;
int		g_ret_status;
t_list	*g_command;
int		g_stop;
struct termios g_old;
struct termios g_new;

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
int		print_prompt(void);
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
void	debug_home(char **input);
void	debug_vars(char	**input);
int		check_quotes(char *str);

/*
**signal.c
*/
void	sigint_handler(int signo);
void	sigint_fork_handler(int signo);
int		eot(char *dst, char *content, int i, int prompt);

/*
**garland.c
*/
char	*get_color(void);

/*
**env2.c
*/
int		env(char **args);
void	print_list_content(t_list *lst);

/*
**parse.c
*/
void	input_str(char *c, int *i, char **str, int prompt);

/*
**terminal.c
*/
int		get_term_input(char **str);

/*
**autocomplete.c
*/
void	autocomplete(int *i, char **str, int prompt);
void	complete_file(char *word, int *i, char **str, int prompt);

/*
**utils.c
*/
int		check_dir(char **path, char **res_dir);
int		symbol_size(char c);
void	replace(char **dst, char *src);
int		get_width(void);
t_list	*copy_lst(t_list *lst);

/*
**control.c
*/
int		handle_back_forward(char *c, int *i, char **str, int prompt);
void	handle_back(int *i, char *str, int prompt);
void	handle_forward(int *i, char *str, int prompt);
int		handle_controls(char *c, int *i, char **str, int prompt);

/*
**overlap.c
*/
int		full_file_list(t_list **lst, char *path, char *word, int n);
int		full_dir_list(t_list **lst, char *path, char *word, int n);
int		full_bin_list(t_list **lst, char *path, char *word, int n);
char	*get_overlap(t_list *lst);

/*
**memcommand.c
*/
char	*memcommand_manager(int mod, char *command);

/*
**carriage.c
*/
void	carriage_down(int len, int i, int prompt);
void	print_memcommand(char *command, char *old, int i, int prompt);
void	back_carriage(char *str, int back, int prompt);

/*
**overlap2.c
*/
int		is_dir(char *path, char *name);
int		full_var_list(t_list **lst, char *word);
int		full_command_list(t_list **lst, char *word);

#endif

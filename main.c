/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achepurn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 21:47:45 by achepurn          #+#    #+#             */
/*   Updated: 2018/03/21 21:47:47 by achepurn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			clear_global(void)
{
	ft_lstdel(&g_env, &ft_memclr);
	g_env = NULL;
	ft_lstdel(&g_undo, &ft_memclr);
	g_undo = NULL;
	ft_lstdel(&g_command, &ft_memclr);
	g_command = NULL;
}

void			init_global(void)
{
	g_env = ft_arrtolst(g_start_env);
	g_undo = NULL;
	g_command = NULL;
}

int				exit_minishell(char **args)
{
	if (!args)
	{
		clear_global();
		exit(g_ret_status);
	}
	if (*args && *(args + 1))
		print_error("exit", "too many arguments\n");
	else
	{
		if (*args)
		{
			if (!ft_isdigit(**args))
				print_error("exit", "numeric argument required\n");
			else
				g_ret_status = ft_atoi(*args);
		}
		clear_global();
		exit(g_ret_status);
	}
	return (1);
}

static void		handle_commands(char *input)
{
	char	**commands;
	size_t	i;

	commands = ft_strsplitmq(input, ";");
	i = -1;
	while (commands[++i])
		execute(commands[i]);
	ft_arrfree(&commands);
}

int				main(int c, char **v, char **e)
{
	char	*input;
 
	(void)c;
	(void)v;
	g_start_env = e;
	init_global();
	while (1)
	{
		//signal(SIGINT, sigint_handler);
		if (get_term_input(&input))
		{
			handle_commands(input);
			memcommand_manager(ADD, input);
			free(input);
		}
	}
}

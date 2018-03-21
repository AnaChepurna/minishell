#include "minishell.h"

void			clear_global(void)
{
	ft_lstdel(&g_env, &ft_memclr);
	g_env = NULL;
	ft_lstdel(&g_undo, &ft_memclr);
	g_undo = NULL;
}

void			init_global(void)
{
	g_env = ft_arrtolst(g_start_env);
	g_undo = NULL;
}

int			exit_minishell(char **args)
{
	clear_global();
	if (*args && *(args + 1))
	{
		print_error("exit", "too many arguments\n");
		g_status = 0;
	}
	else
	{
		if (*args)
		{
			g_status = ft_atoi(*args);
			if (!g_status)
				g_status = 1;
		}
		exit(g_status);
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
	g_status = 0;
	init_global();
	while(1)
	{
		print_prompt();
		signal(SIGINT, sigint_handler);
		if ((input = get_input()))
		{
			handle_commands(input);
			free(input);
		}
	}
}
#include "minishell.h"

void			clear_global(void)
{
	ft_lstdel(&g_env, &ft_memclr);
	ft_lstdel(&g_undo, &ft_memclr);
}

void			init_global(void)
{
	g_env = ft_arrtolst(g_start_env);
	g_undo = NULL;
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
	while(1)
	{
		print_prompt();
		if (get_next_line(1, &input) > 0)
		{
			handle_commands(input);
			free(input);
		}
	}
}
#include "minishell.h"

static void		handle_commands(char *input)
{
	char	**commands;
	size_t	i;

	commands = ft_strsplit(input, ';');
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
	g_env = ft_arrtolst(e);
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
#include "minishell.h"

void	process(char *command)
{
	if (ft_strequ(command, "exit"))
		exit(1);
}

int		main(int c, char **v, char **e)
{
	char	*input;

	while(1)
	{
		ft_putstr( MAGENTA "♥" RESET " > ");
		if (get_next_line(1, &input) > 0)
		{
			process(input);
			free(input);
		}
	}
}
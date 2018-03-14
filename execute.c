#include "minishell.h"

static int	exec_bin(char **args)
{
	return (0);
}

static int	exec_builtin(char **args)
{

}

void		execute(char *command)
{
	char	**args;

	args = ft_strsplit(command, ' ');
	if (!(exec_builtin(args) || exec_builtin(args)))
		print_error_arg(args[0]);
}
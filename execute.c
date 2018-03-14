#include "minishell.h"

static int	exec_bin(char **args)
{
	(void)args;
	return (0);
}

static int	exec_builtin(char **args)
{
	if (ft_strequ(args[0], "exit"))
		exit_minishell();
	if (ft_strequ(args[0], "env"))
		return (print_env());
	return (0);
}

void		execute(char *command)
{
	char	**args;

	args = ft_strsplit(command, ' ');
	if (!(exec_bin(args) || exec_builtin(args)))
		print_error_arg(args[0]);
	ft_arrfree(&args);
}
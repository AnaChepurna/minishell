#include "minishell.h"

void	print_prompt(void)
{
	ft_putstr( MAGENTA "♥" RESET " > ");
}

void	print_error_arg(char *arg)
{
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": command not found\n", 2);
}

int		print_env(void)
{
	t_list	*lst;

	lst = g_env;
	while (lst)
	{
		ft_putendl((char *)lst->content);
		lst = lst->next;
	}
	return (1);
}

int		echo(char **args)
{
	int		n;

	if (!args)
		ft_putstr("\n");
	else
	{
		n = ft_strequ(*args, "-n");
		if (n)
			args++;
		while (*args)
		{
			ft_putstr(*args);
			if (*(args + 1))
				ft_putstr(" ");
			args++;
		}
		if (!n)
			ft_putstr("\n");
	}
	return (1);
}
#include "minishell.h"

void	print_prompt(void)
{
	char	*color;

	color = get_color();
	ft_putstr(color);
	ft_putstr("♥" RESET " > ");
}

void	print_error(char *arg, char *msg)
{
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(msg, 2);
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

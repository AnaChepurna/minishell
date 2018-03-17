#include "minishell.h"

void	sigint_handler(int signo)
{
	if (signo == SIGINT)
	{
		ft_putstr("\n");
		print_prompt();
		signal(SIGINT, sigint_handler);
	}
}

void	sigint_fork_handler(int signo)
{
	if (signo == SIGINT)
	{
		ft_putstr("\n");
		signal(SIGINT, sigint_fork_handler);
	}
}

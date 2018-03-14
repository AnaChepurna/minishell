#include "minishell.h"

void	print_prompt(void)
{
	ft_putstr( MAGENTA "♥" RESET " > ");
}

void	print_error_arg(char *arg)
{
	ft_putstr_fd(2, arg);
	ft_putstr_fd(2, ": command not found\n");
}

void	print_env(void)
{
	t_list	*lst;

	lst = g_env;
	while (lst)
	{
		ft_putstr((char *)lst->content);
		lst = lst->next;
	}
}

void	exit_minishell(void)
{
	ft_lstdel(&g_env, &ft_memclr)
}
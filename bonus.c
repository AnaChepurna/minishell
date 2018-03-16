#include "minishell.h"

static void		__unset_var(char *var_name)
{
	t_list	*lst;
	size_t	len;
	int		i;

	lst = g_env;
	len = ft_strlen(var_name);
	i = 0;
	while (lst)
	{
		if (ft_strnequ(var_name, (char *)lst->content, len))
		{
			lst = ft_lstrm(&g_env, i);
			break ;
		}
		i++;
		lst = lst->next;
	}
}

static void		undo_var(char *var_name)
{
	t_list	*lst;
	size_t	i;
	size_t	len;

	lst = g_undo;
	i = 0;
	len = ft_strlen(var_name);
	while (lst)
	{
		if (ft_strnequ(var_name, (char *)lst->content, len))
		{
			lst = ft_lstrm(&g_undo, i);
			break ;
		}
		lst = lst->next;
		i++;
	}
	if (lst)
	{
		__unset_var(var_name);
		ft_lstaddend(&g_env, ft_lstnew((char *)lst->content,
			ft_strlen((char *)lst->content) + 1));
		ft_lstdelone(&lst, &ft_memclr);
	}
}

int				undoenv(char **args)
{
	while (*args)
	{
		undo_var(*args);
		args++;
	}
	return (1);
}
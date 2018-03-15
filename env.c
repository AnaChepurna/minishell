#include "minishell.h"

char	*get_var(char *var_name)
{
	t_list	*lst;
	size_t	len;

	lst = g_env;
	len = ft_strlen(var_name);
	while (lst)
	{
		if (ft_strnequ(var_name, (char *)lst->content, len))
			return ((char *)lst->content + len);
		lst = lst->next;
	}
	return (NULL);
}

int		unset_var(char *var_name)
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
			ft_lstrm(g_env, i);
			break ;
		}
		i++;
		lst = lst->next;
	}
	return (1);
}

int		set_var(char *var_name, char *value)
{
	char	*content;

	content = ft_strjoin(var_name, value);
	unset_var(var_name);
	ft_lstadd(&g_env, ft_lstnew(content, ft_strlen(content) + 1));
	free(content);
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
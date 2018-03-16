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

void		unset_var(char *var_name)
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
			ft_lstadd(&g_undo, lst);
			break ;
		}
		i++;
		lst = lst->next;
	}
}

void		set_var(char *var_name, char *value)
{
	char	*content;

	if (!value)
		return ;
	content = ft_strjoin(var_name, value);
	unset_var(var_name);
	ft_lstaddend(&g_env, ft_lstnew(content, ft_strlen(content) + 1));
	free(content);
}

int		ft_unsetenv(char **args)
{
	char	*name;

	while (*args)
	{
		name = ft_strjoin(*args, "=");
		unset_var(name);
		free(name);
		args++;
	}
	return (1);
}

int		ft_setenv(char **args)
{
	char	**vars;
	char	*name;

	while (*args)
	{
		vars = ft_strsplit(*args, '=');
		name = ft_strjoin(vars[0], "=");
		set_var(name, vars[1]);
		free(name);
		ft_arrfree(&vars);
		args++;
	}
	return (1);
}

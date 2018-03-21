/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achepurn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 21:46:52 by achepurn          #+#    #+#             */
/*   Updated: 2018/03/21 21:46:58 by achepurn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_var(t_list *env, char *var_name)
{
	t_list	*lst;
	size_t	len;

	lst = env;
	len = ft_strlen(var_name);
	while (lst)
	{
		if (ft_strnequ(var_name, (char *)lst->content, len))
			return ((char *)lst->content + len);
		lst = lst->next;
	}
	return (NULL);
}

int		unset_var(char *var_name, int save)
{
	t_list	*lst;
	int		i;
	char	*buf;

	if (!var_name)
		print_error("unsetenv", "too few arguments\n");
	lst = g_env;
	buf = ft_strjoin(var_name, "=");
	i = 0;
	while (lst)
	{
		if (ft_strnequ(buf, (char *)lst->content, ft_strlen(buf)))
		{
			lst = ft_lstrm(&g_env, i);
			if (save)
				ft_lstadd(&g_undo, lst);
			else
				ft_lstdelone(&lst, &ft_memclr);
			break ;
		}
		i++;
		lst = lst->next;
	}
	free(buf);
	return (1);
}

int			set_var(char *var_name, char *value, int save)
{
	char	*content;
	char	*buf;

	if (!var_name)
	{
		ft_lstiter(g_env, &print_list_content);
		return (1);
	}
	if (!value)
		return (1);
	buf = ft_strjoin(var_name, "=");
	content = ft_strjoin(buf, value);
	free(buf);
	unset_var(var_name, save);
	ft_lstaddend(&g_env, ft_lstnew(content, ft_strlen(content) + 1));
	free(content);
	return (1);
}

int			undo_var(char *var_name)
{
	t_list	*lst;
	size_t	i;
	size_t	len;

	if (!var_name)
		print_error("undoenv", "too few arguments\n");
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
		set_var(var_name, (char *)lst->content + len + 1, 0);
		ft_lstdel(&lst, &ft_memclr);
	}
	return (1);
}

int			reset_env(void)
{
	clear_global();
	init_global();
	return (1);
}

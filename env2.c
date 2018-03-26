/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achepurn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 21:47:08 by achepurn          #+#    #+#             */
/*   Updated: 2018/03/21 21:47:10 by achepurn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void				print_list_content(t_list *lst)
{
	ft_putendl((char *)lst->content);
}

static void			set_env_var(t_list **env, char *str, int size)
{
	t_list	*lst;
	int		i;

	lst = *env;
	i = 0;
	while (lst)
	{
		if (ft_strnequ((char *)lst->content, str, size))
		{
			lst = ft_lstrm(env, i);
			ft_lstdelone(&lst, &ft_memclr);
			break ;
		}
		i++;
		lst = lst->next;
	}
	ft_lstaddend(env, ft_lstnew(str, ft_strlen(str) + 1));
}

int					env(char **args)
{
	t_list	*env;
	char	*ptr;
	int		flag_i;

	env = NULL;
	flag_i = 0;
	if (ft_strequ(*args, "-i"))
	{
		flag_i = 1;
		args++;
	}
	if (!flag_i)
		env = ft_lstmap(g_env, &copy_lst);
	while ((ptr = ft_strchr(*args, '=')))
	{
		set_env_var(&env, *args, ptr - *args);
		args++;
	}
	if (!(*args))
		ft_lstiter(env, &print_list_content);
	else if (!exec_bin(args, env))
		print_error(*args, "no such file or directory\n");
	ft_lstdel(&env, &ft_memclr);
	return (1);
}

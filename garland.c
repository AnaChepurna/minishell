/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garland.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achepurn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 21:47:26 by achepurn          #+#    #+#             */
/*   Updated: 2018/03/21 21:47:28 by achepurn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_list	*maping(t_list *lst)
{
	char	*color_code;
	char	*color_name;

	color_name = (char *)lst->content;
	if (ft_strequ(color_name, "blue"))
		color_code = BLUE;
	else if (ft_strequ(color_name, "red"))
		color_code = RED;
	else if (ft_strequ(color_name, "green"))
		color_code = GREEN;
	else if (ft_strequ(color_name, "yellow"))
		color_code = YELLOW;
	else if (ft_strequ(color_name, "cyan"))
		color_code = CYAN;
	else if (ft_strequ(color_name, "white"))
		color_code = WHITE;
	else
		color_code = MAGENTA;
	return (ft_lstnew(color_code, ft_strlen(color_code) + 1));
}

static t_list	*create_cycle(char *str)
{
	char	**vars;
	t_list	*proto;
	t_list	*res;
	t_list	*res_end;

	vars = ft_strsplit(str, ':');
	proto = ft_arrtolst(vars);
	res = ft_lstmap(proto, &maping);
	res_end = res;
	while (res_end->next)
		res_end = res_end->next;
	res_end->next = res;
	ft_lstdel(&proto, &ft_memclr);
	ft_arrfree(&vars);
	return (res_end);
}

static void		init_list(char *str, t_list **list)
{
	t_list	*start;

	if (*list)
	{
		start = (*list)->next;
		(*list)->next = NULL;
		ft_lstdel(&start, &ft_memclr);
	}
	*list = create_cycle(str);
}

char			*get_color(void)
{
	static t_list	*list = NULL;
	static char		*oldenv = NULL;
	char			*newenv;

	newenv = get_var(g_env, "GARLAND=");
	if (!newenv)
		return (MAGENTA);
	else if (!ft_strequ(oldenv, newenv))
	{
		init_list(newenv, &list);
		free(oldenv);
		oldenv = ft_strdup(newenv);
	}
	list = list->next;
	return ((char *)list->content);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memcommand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achepurn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 13:55:37 by achepurn          #+#    #+#             */
/*   Updated: 2018/03/30 13:55:38 by achepurn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		add_command(char *command)
{
	t_list	*current;
	int		i;

	current = g_command;
	i = 0;
	while (current)
	{
		if (ft_strequ((char*)current->content, command))
		{
			current = ft_lstrm(&g_command, i);
			break ;
		}
		i++;
		current = current->next;
	}
	if (!current)
		current = ft_lstnew(command, ft_strlen(command) + 1);
	ft_lstadd(&g_command, current);
}

static char		*up_command(t_list **up, t_list **down)
{
	char	*res;
	int		n;
	int		len;

	if (!*down && !*up)
		*up = ft_lstmap(g_command, &copy_lst);
	if (*up)
		ft_lstadd(down, (ft_lstpop(up)));
	if (*down)
	{
		len = ft_strlen((char *)(*down)->content);
		n = 1;
		while (n * BUFF_SIZE < len)
			n++;
		res = ft_strnew(BUFF_SIZE * ++n + 1);
		return (ft_strcpy(res, (char *)(*down)->content));
	}
	else
		return (NULL);
}

static char		*down_command(t_list **up, t_list **down)
{
	char	*res;
	int		len;
	int		n;

	if (*down)
		ft_lstadd(up, (ft_lstpop(down)));
	if (*down)
	{
		len = ft_strlen((char *)(*down)->content);
		n = 1;
		while (n * BUFF_SIZE < len)
			n++;
		res = ft_strnew(BUFF_SIZE * ++n + 1);
		return (ft_strcpy(res, (char *)(*down)->content));
	}
	else
		return (ft_strnew(BUFF_SIZE + 1));
}

char			*memcommand_manager(int mod, char *command)
{
	static t_list	*down = NULL;
	static t_list	*up = NULL;

	if (mod == ADD)
	{
		ft_lstdel(&down, &ft_memclr);
		ft_lstdel(&up, &ft_memclr);
		add_command(command);
		return (NULL);
	}
	if (mod == UP)
		return (up_command(&up, &down));
	if (mod == DOWN)
		return (down_command(&up, &down));
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achepurn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 13:54:39 by achepurn          #+#    #+#             */
/*   Updated: 2018/03/30 13:54:42 by achepurn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			handle_back(int *i, char *str, int prompt)
{
	int		width;
	int		real_i;

	if (!str)
		return ;
	width = get_width();
	real_i = ft_wstrlen(str) - ft_wstrlen(str + *i);
	if (*i)
	{
		if ((real_i + prompt) % width == 0)
		{
			ft_putstr("[A");
			while (width--)
				ft_putstr("[C");
		}
		else
			ft_putstr("[D");
		(*i)--;
		while (str[*i] < 0 && !(str[*i] & 64))
			(*i)--;
	}
}

void			handle_forward(int *i, char *str, int prompt)
{
	int		width;
	int		real_i;

	if (!str)
		return ;
	width = get_width();
	real_i = ft_wstrlen(str) - ft_wstrlen(str + *i);
	if (*i >= ft_strlen(str))
		return ;
	if ((real_i + prompt) % width == width - 1)
	{
		ft_putstr("\r");
		ft_putstr("[B");
	}
	else
		ft_putstr("[C");
	(*i) += symbol_size(str[*i]);
}

int				handle_back_forward(char *c, int *i, char **str, int prompt)
{
	if (ft_strequ(c, "\t"))
	{
		autocomplete(i, str, prompt);
		return (1);
	}
	if (ft_strequ(c, "[D"))
	{
		handle_back(i, *str, prompt);
		return (1);
	}
	if (ft_strequ(c, "[C"))
	{
		handle_forward(i, *str, prompt);
		return (1);
	}
	return (0);
}

int				handle_controls(char *c, int *i, char **str, int prompt)
{
	char	*command;

	if (ft_strequ(c, "[A"))
	{
		command = memcommand_manager(UP, NULL);
		if (!command)
			return (1);
		print_memcommand(command, *str, *i, prompt);
		free(*str);
		*str = command;
		*i = ft_strlen(command);
		return (1);
	}
	else if (ft_strequ(c, "[B"))
	{
		command = memcommand_manager(DOWN, NULL);
		if (!command)
			return (1);
		print_memcommand(command, *str, *i, prompt);
		free(*str);
		*str = command;
		*i = ft_strlen(command);
		return (1);
	}
	return (0);
}

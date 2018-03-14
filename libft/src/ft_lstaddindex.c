/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstaddindex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achepurn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 13:34:03 by achepurn          #+#    #+#             */
/*   Updated: 2017/11/18 21:28:19 by achepurn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstaddindex(t_list **alst, t_list *new, int index)
{
	t_list	*current;
	t_list	*buf;
	int		i;

	if (!alst || !(*alst) || !new)
		return ;
	if (index == 0)
		ft_lstadd(alst, new);
	else
	{
		current = *alst;
		i = 0;
		while (i < index - 1 && current)
			current = current->next;
		if (current)
		{
			buf = current->next;
			current->next = new;
			new->next = buf;
		}
	}
}

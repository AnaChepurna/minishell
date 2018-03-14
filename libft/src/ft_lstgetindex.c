/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstgetindex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achepurn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 14:44:09 by achepurn          #+#    #+#             */
/*   Updated: 2017/11/18 21:29:23 by achepurn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstgetindex(t_list *begin, t_list *lst)
{
	int	i;

	if (!begin || !lst)
		return (-1);
	i = 0;
	while (begin)
	{
		if (ft_strnequ((char *)lst->content, (char *)begin->content,
begin->content_size))
			return (i);
		i++;
		begin = begin->next;
	}
	return (-1);
}

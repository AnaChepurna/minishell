/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstprint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achepurn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 13:57:18 by achepurn          #+#    #+#             */
/*   Updated: 2017/11/18 21:30:55 by achepurn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstprint(t_list *lst)
{
	if (!lst)
		return ;
	ft_putendl("-------");
	ft_putstr("content: ");
	if (lst->content)
		ft_putendl((char *)lst->content);
	ft_putstr("content_size: ");
	ft_putnbr(lst->content_size);
	ft_putchar('\n');
	if (lst->next)
		ft_putendl("next: present");
	else
		ft_putendl("next: no");
	ft_putendl("-------");
}

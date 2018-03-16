/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstrm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achepurn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 14:43:35 by achepurn          #+#    #+#             */
/*   Updated: 2017/11/18 21:31:18 by achepurn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstrm(t_list **alst, int index)
{
	t_list	*current;
	t_list	*last;

	if (!alst || !(*alst) || index < 0)
		return (NULL);
	if (!index)
		return (ft_lstpop(alst));
	last = ft_lstget(*alst, index - 1);
	current = last->next;
	last->next = current->next;
	current->next = NULL;
	return (current);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achepurn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 14:44:28 by achepurn          #+#    #+#             */
/*   Updated: 2017/11/18 21:30:38 by achepurn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstpop(t_list **alst)
{
	t_list	*current;

	if (!alst || !(*alst))
		return (NULL);
	current = *alst;
	*alst = (*alst)->next;
	current->next = NULL;
	return (current);
}

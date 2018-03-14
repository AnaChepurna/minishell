/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstget.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achepurn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 14:44:52 by achepurn          #+#    #+#             */
/*   Updated: 2017/11/18 21:29:01 by achepurn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstget(t_list *lst, int index)
{
	if (!lst || index < 0)
		return (NULL);
	if (index > 0)
		return (ft_lstget(lst->next, --index));
	return (lst);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrtolst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achepurn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 13:27:52 by achepurn          #+#    #+#             */
/*   Updated: 2017/11/20 11:31:00 by achepurn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_arrtolst(char **arr)
{
	t_list	*current;

	if (*arr)
	{
		current = ft_lstnew((void *)*arr, sizeof(char) * (ft_strlen(*arr) + 1));
		current->next = ft_arrtolst(++arr);
		return (current);
	}
	return (NULL);
}

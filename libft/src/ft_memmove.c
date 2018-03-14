/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achepurn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 13:03:25 by achepurn          #+#    #+#             */
/*   Updated: 2017/11/24 14:52:00 by achepurn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char			*ptr1;
	const char		*ptr2;
	size_t			i;

	if (!dest || !src || !n || dest == src)
		return (dest);
	ptr1 = dest;
	ptr2 = src;
	i = -1;
	if (ptr2 < ptr1)
		while ((int)(--n) >= 0)
			ptr1[n] = ptr2[n];
	else
		while (++i < n)
			ptr1[i] = ptr2[i];
	return (dest);
}

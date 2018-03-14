/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achepurn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 13:12:17 by achepurn          #+#    #+#             */
/*   Updated: 2017/11/20 11:37:37 by achepurn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	const char		*ptr;

	if (!s)
		return (NULL);
	ptr = s;
	i = 0;
	while (i < n)
	{
		if (ptr[i] == (char)c)
			return ((void *)ptr + i);
		i++;
	}
	return (NULL);
}

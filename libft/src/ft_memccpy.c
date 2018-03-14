/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achepurn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 13:07:36 by achepurn          #+#    #+#             */
/*   Updated: 2017/11/22 16:01:41 by achepurn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*ptr1;
	const char		*ptr2;

	if (!dest || !src)
		return (NULL);
	ptr1 = dest;
	ptr2 = src;
	i = 0;
	while (i < n)
	{
		ptr1[i] = ptr2[i];
		if (ptr1[i] == (unsigned char)c)
			return ((unsigned char *)(ptr1 + i + 1));
		i++;
	}
	return (NULL);
}

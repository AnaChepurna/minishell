/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achepurn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 12:59:33 by achepurn          #+#    #+#             */
/*   Updated: 2017/11/20 11:41:53 by achepurn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *memptr, int val, size_t num)
{
	size_t			i;
	unsigned char	*buf;

	if (!memptr)
		return (NULL);
	i = 0;
	buf = memptr;
	while (i < num)
	{
		buf[i] = (unsigned char)val;
		i++;
	}
	return (memptr);
}

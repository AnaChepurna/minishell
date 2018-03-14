/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achepurn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 13:20:25 by achepurn          #+#    #+#             */
/*   Updated: 2017/11/20 11:49:58 by achepurn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t l)
{
	size_t	i;
	size_t	j;

	if (!dest || !src)
		return (0);
	i = 0;
	j = 0;
	while (dest[i])
		i++;
	while (src[j] && (int)i + (int)j < (int)l - 1)
	{
		dest[i + j] = src[j];
		j++;
	}
	dest[i + j] = '\0';
	while (src[j])
		j++;
	if (i > l)
		return (l + j);
	return (i + j);
}

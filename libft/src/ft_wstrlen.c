/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wstrlen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achepurn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 14:21:01 by achepurn          #+#    #+#             */
/*   Updated: 2018/02/12 14:21:13 by achepurn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_wstrlen(char *str)
{
	size_t	len;
	char	buf;

	len = 0;
	while (*str)
	{
		if (*str < 0)
		{
			buf = *str;
			while (buf < 0)
			{
				str++;
				buf = buf << 1;
			}
		}
		else
			str++;
		len++;
	}
	return (len);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achepurn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 20:36:05 by achepurn          #+#    #+#             */
/*   Updated: 2017/11/20 11:52:04 by achepurn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char			*str;
	size_t			i;

	str = (char *)malloc(size + 1);
	if (str)
	{
		i = 0;
		while (i <= size)
			str[i++] = '\0';
	}
	return (str);
}

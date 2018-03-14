/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achepurn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 10:33:41 by achepurn          #+#    #+#             */
/*   Updated: 2017/11/18 21:52:07 by achepurn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*res;
	int		i;

	if (s && f)
	{
		res = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
		if (res)
		{
			i = 0;
			while (s[i])
			{
				res[i] = (*f)(s[i]);
				i++;
			}
			res[i] = '\0';
			return (res);
		}
	}
	return (NULL);
}

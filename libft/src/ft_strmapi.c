/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achepurn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 11:33:28 by achepurn          #+#    #+#             */
/*   Updated: 2017/11/18 21:52:20 by achepurn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*res;
	unsigned int	i;

	if (s && f)
	{
		res = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
		if (res)
		{
			i = 0;
			while (s[i])
			{
				res[i] = (*f)(i, s[i]);
				i++;
			}
			res[i] = '\0';
			return (res);
		}
	}
	return (NULL);
}

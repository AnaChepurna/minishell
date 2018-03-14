/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achepurn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 16:34:01 by achepurn          #+#    #+#             */
/*   Updated: 2017/11/25 21:53:17 by achepurn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		split_len(const char *str, char c)
{
	int		i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (++i);
}

static int		recursive_count(const char *str, char c)
{
	if (*str == c)
		return (recursive_count(++str, c));
	if (*str)
	{
		while (*str != c && *str)
			str++;
		return (1 + recursive_count(str, c));
	}
	else
		return (0);
}

static int		recursive_split(char **dst, const char *str, char c)
{
	char	*res;
	int		i;

	if (*str == c)
		return (recursive_split(dst, ++str, c));
	if (*str)
	{
		if (!(res = (char *)malloc(sizeof(char) * split_len(str, c))))
			return (0);
		i = 0;
		while (*str && *str != c)
		{
			res[i] = *str;
			i++;
			str++;
		}
		res[i] = '\0';
		*dst = res;
		return (recursive_split(++dst, str, c));
	}
	*dst = NULL;
	return (1);
}

char			**ft_strsplit(const char *s, char c)
{
	int		len;
	char	**res;

	if (!s)
		return (NULL);
	len = recursive_count(s, c);
	if ((res = (char **)malloc(sizeof(char *) * (len + 1))))
		if (!recursive_split(res, s, c))
			ft_arrfree(&res);
	return (res);
}

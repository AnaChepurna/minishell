/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achepurn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 12:51:02 by achepurn          #+#    #+#             */
/*   Updated: 2017/12/18 14:36:26 by achepurn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	a_len(uintmax_t n, int base)
{
	size_t	res;

	if (n == 0)
		return (2);
	res = 1;
	while (n != 0)
	{
		res++;
		n /= base;
	}
	return (res);
}

static void		put_a(uintmax_t n, char *str, int len, int base)
{
	char	*map;

	map = "0123456789abcdefghijklmnopqrstuvwxyz";
	str[len] = '\0';
	len--;
	while (n >= (unsigned int)base)
	{
		str[len] = map[n % base];
		n /= base;
		len--;
	}
	str[len] = map[n];
}

char			*ft_itoa_base(uintmax_t n, int base)
{
	char	*res;
	size_t	len;

	if (base < 2 || base > 36)
		return (NULL);
	len = a_len(n, base);
	res = (char*)malloc(sizeof(char) * len);
	put_a(n, res, len - 1, base);
	return (res);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achepurn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 13:31:52 by achepurn          #+#    #+#             */
/*   Updated: 2017/11/18 21:14:18 by achepurn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_inmap(char c, char *map, int base)
{
	int		i;

	i = 0;
	while (i < base)
	{
		if (map[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static int	get_number(char c, char *map, int base)
{
	int		i;

	i = 0;
	while (i < base)
	{
		if (map[i] == c)
			return (i);
		i++;
	}
	return (0);
}

int			ft_atoi_base(char *str, int base)
{
	int		i;
	int		result;
	char	*map;
	char	c;

	if (!str || base < 2 || base > 36)
		return (0);
	if (base == 10)
		return (ft_atoi(str));
	map = "0123456789abcdefghijklmnopqrstuvwxyz";
	result = 0;
	i = 0;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t' ||
			str[i] == '\v' || str[i] == '\r' || str[i] == '\f')
		i++;
	while (is_inmap((c = ft_tolower(str[i])), map, base))
	{
		result *= base;
		result += get_number(c, map, base);
		i++;
	}
	return (result);
}

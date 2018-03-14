/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achepurn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 14:25:01 by achepurn          #+#    #+#             */
/*   Updated: 2018/02/12 14:25:03 by achepurn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_arrrev(void **arr)
{
	size_t	len;
	size_t	half;
	size_t	i;

	len = ft_arrlen(arr);
	half = len-- / 2;
	i = 0;
	while (i < half)
	{
		ft_swap(arr + i, arr + len - i);
		i++;
	}
}

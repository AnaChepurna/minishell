/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achepurn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 13:55:26 by achepurn          #+#    #+#             */
/*   Updated: 2018/03/30 13:55:28 by achepurn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		delete_quotes(char **input, int i)
{
	char	*res;
	char	*ptr;

	while ((*input)[i])
	{
		ptr = NULL;
		if (IS_QUOTE((*input)[i]) &&
			(ptr = ft_strchr(*input + i + 1, (*input)[i])))
			break ;
		i++;
	}
	if (ptr && (res = ft_strnew(ft_strlen(*input) - 2)))
	{
		ft_strncpy(res, *input, i);
		ft_strncpy(res + i, *input + i + 1, ptr - *input - i - 1);
		ft_strcpy(res + (ptr - *input) - 1, *input + (ptr - *input) + 1);
		i = ptr - *input;
		free(*input);
		*input = res;
		delete_quotes(input, i);
	}
}

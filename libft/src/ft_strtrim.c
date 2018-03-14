/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achepurn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 13:31:13 by achepurn          #+#    #+#             */
/*   Updated: 2017/11/18 21:57:55 by achepurn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	int		start;
	int		finish;
	char	*res;

	if (!s)
		return (NULL);
	start = 0;
	while (s[start] == ' ' || s[start] == '\n' || s[start] == '\t')
		start++;
	finish = ft_strlen(s) - 1;
	if (start > finish)
	{
		res = (char*)malloc(sizeof(char) * 1);
		res[0] = '\0';
		return (res);
	}
	while (s[finish] == ' ' || s[finish] == '\n' || s[finish] == '\t')
		finish--;
	res = (char *)malloc(sizeof(char) * (finish - start + 2));
	if (res)
	{
		ft_strncpy(res, &s[start], finish - start + 1);
		res[finish - start + 1] = '\0';
	}
	return (res);
}

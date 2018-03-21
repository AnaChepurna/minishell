/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pathjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achepurn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 21:51:26 by achepurn          #+#    #+#             */
/*   Updated: 2018/03/21 21:51:48 by achepurn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_pathjoin(char *path, char *name)
{
	char	*res;
	char	*buf;
	int		len;

	if (!path)
		return (ft_strdup(name));
	len = ft_strlen(path);
	while (path[--len] == '/')
		path[len] = '\0';
	buf = ft_strjoin(path, "/");
	res = ft_strjoin(buf, name);
	free(buf);
	return (res);
}

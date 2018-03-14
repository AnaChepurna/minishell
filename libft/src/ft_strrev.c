#include "libft.h"

#include <stdio.h>

void	ft_strrev(char *str)
{
	char	*buf;
	size_t	len;
	size_t	i;

	buf = ft_strdup(str);
	len = ft_strlen(str);
	i = 0;
	while (i < len)
	{
		str[i] = buf[len - 1 - i];
		i++;
	}
	free(buf);
}
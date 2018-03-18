#include "libft.h"

void		delete_quotes(char **input)
{
	char	c;
	char	*ptr[2];
	char	*res;
	size_t	j;
	size_t	i;

	ptr[0] = ft_strchr(*input, '"');
	ptr[1] = ft_strchr(*input, '\'');
	if (!ptr[0] && !ptr[1])
		return ;
	else if (ptr[0] && ptr[1])
		c = ptr[0] < ptr[1] ? '"' : '\'';
	else 
		c = (ptr[0])? '"' : '\'';
	if ((res = ft_strnew(ft_strlen(*input) - 2)))
	{
		i = 0;
		j = 0;
		while ((*input)[j])
			if ((*input)[j++] != c)
				res[i++] = (*input)[j - 1];
		free(*input);
		*input = res;
	}
}
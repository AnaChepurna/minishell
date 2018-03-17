#include "minishell.h"

int			check_quotes(char *str)
{
	int		res;
	char	c;

	if (!str)
		return (0);
	res = 1;
	c = 0;
	while (*str)
	{
		if (*str == '\'' || *str == '"')
		{
			if (!c)
			{
				c = *str;
				res = 0;
			}
			else if (c == *str)
			{
				c = 0;
				res = 1;
			}
		}
		str++;
	}
	return (res);
}

char		*get_input(void)
{
	char	*input;
	char	*buff;
	char	*res;

	get_next_line(0, &res);
	input = ft_strjoin("", res);
	while (!check_quotes(input))
	{
		buff = input;
		input = ft_strjoin(buff, "\n");
		free(buff);
		buff = input;
		ft_putstr("quote> ");
		get_next_line(0, &res);
		input = ft_strjoin(buff, res);
		free(buff);
		free(res);
	}
	return (input);
}

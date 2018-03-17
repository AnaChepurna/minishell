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

int			get_next_line_handler(char **str, int quote)
{
	int ret;

	ret = get_next_line(0, str);
	if (!ret && quote)
	{
		print_error("minishell", "syntax problem: unexpected EOF\n");
		return (0);
	}
	if (!ret)
	{
		clear_global();
		exit(1);
	}
	if (ret == -1)
	{
		print_error("minishell", "input problem. The process will be ended\n");
		clear_global();
		exit(1);
	}
	return (1);
}

char		*get_input(void)
{
	char	*input;
	char	*buff;
	char	*res;

	if (!get_next_line_handler(&res, 0))
		return (NULL);
	input = ft_strjoin("", res);
	free(res);
	while (!check_quotes(input))
	{
		buff = input;
		input = ft_strjoin(buff, "\n");
		free(buff);
		buff = input;
		ft_putstr("quote> ");
		if (!get_next_line_handler(&res, 1))
		{
			free(buff);
			return (NULL);
		}
		input = ft_strjoin(buff, res);
		free(buff);
		free(res);
	}
	return (input);
}

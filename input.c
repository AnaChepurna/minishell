#include "minishell.h"

void		debug_specials(char **input)
{
	char	*ptr;
	char	*src;
	char	*res;
	size_t	len;

	if ((ptr = ft_strchr(*input, '~')) == *input) 
	{
		src = get_var("HOME=");
		len = ft_strlen(src);
		if ((res = ft_strnew(len + ft_strlen(*input + 1))))
		{
			ft_strcpy(res, src);
			ft_strcpy(res + len, *input + 1);
			free(*input);
			*input = res;
		}
	}
}

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
	else if (ptr[0])
		c = '"';
	else if (ptr[1])
		c = '\'';
	if ((res = ft_strnew(ft_strlen(*input) - 2)))
	{
		i = 0;
		j = 0;
		while ((*input)[j])
		{
			if ((*input)[j] != c)
				res[i++] = (*input)[j];
			j++;
		}
		free(*input);
		*input = res;
	}
}

static int	check_quotes(char *str)
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

static int	get_next_line_handler(char **str, int quote)
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

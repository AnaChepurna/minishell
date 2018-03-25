/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achepurn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 21:47:35 by achepurn          #+#    #+#             */
/*   Updated: 2018/03/21 21:47:37 by achepurn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		debug_home(char **input)
{
	char	*ptr;
	char	*src;
	char	*res;
	size_t	len;

	if ((ptr = ft_strchr(*input, '~')) == *input)
	{
		src = get_var(g_env, "HOME=");
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

int			count_word(char *str)
{
	int i;

	i = 0;
	while (str[i] && !IS_SPACE(str[i]))
		i++;
	return (i);
}

void		debug_vars(char	**input)
{
	char	*res;
	char	*ptr;
	char	*v[2];
	int		len[2];

	if ((ptr = ft_strchr(*input, '$')))
	{
		v[0] = ft_strsub(ptr, 1, count_word(ptr));
		v[1] = ft_strnequ(v[0], "?", 1) ?
		ft_itoa(g_ret_status) : ft_strdup(get_var(g_env, v[0]));
		len[0] = ft_strlen(v[0]) + 1;
		len[1] = ft_strlen(v[1]);
		if ((res = ft_strnew(ft_strlen(*input) - len[0] + len[1])))
		{
			ft_strncpy(res, *input, ptr - *input);
			ft_strcpy(res + (ptr - *input), v[1]);
			ft_strcpy(res + (ptr - *input) + len[1], *input + len[0]);
			free(*input);
			*input = res;
		}
		free(v[0]);
		free(v[1]);
		debug_vars(input);
	}
} 

void		debug_eof(char **input)
{
	char	*ptr;
	char	*res;
	size_t	i;

	if ((ptr = ft_strchr(*input, '$')) &&
		ptr[1] && !(IS_SPACE(ptr[1])) && ptr[1] != '?')
	{
		ft_putendl(*input);
		i = 0;
		while (ptr[i] && !(IS_SPACE(ptr[i])))
			i++;
		if ((res = ft_strnew(ft_strlen(*input) - i + 1)))
		{
			ft_strncpy(res, *input, ptr - *input);
			ft_strcpy(res + (ptr - *input), ptr + i);
			free(*input);
			*input = res;
			debug_eof(input);
		}
	}
}

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
	if (ft_strchr(*str, 3))
		return (0);
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

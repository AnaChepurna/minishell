#include "minishell.h"

static void		check_size(char	*c, char **str)
{
	static int	n = 0;
	static int	rank = 1;
	char		*buf;

	n += ft_strlen(c);
	if (n > BUFF_SIZE)
	{
		while (n > BUFF_SIZE)
		{
			n -= BUFF_SIZE;
			rank++;
		}
		if ((buf = ft_strnew(BUFF_SIZE * rank)))
		{
			n = 0;
			ft_strcpy(buf, *str);
			free(*str);
			*str = buf;
		}
		/*else
		{
			print_error("minishell", "memory error\n")
			exit_minishell();
		}*/
	}
}

void			print_teil(char *buf)
{
	size_t	len;

	len = ft_strlen(buf);
	ft_putstr(buf);
	ft_putstr("    \b\b\b\b");
	while (len--)
		ft_putstr("\b");
}

void			input_str(char *c, int *i, char **str)
{
	char		*buf;
	int			mod;

	check_size(c, str);
	mod =  ft_strequ("[3~", c) ? 2 : 0;
	mod = (c[0] == 127 && !c[1]) ? 1 : mod;
	buf = mod == 2 ? ft_strdup(*str + *i + 1) : ft_strdup(*str + *i);
	if (!mod)
	{
		ft_putstr(c);
		ft_strcpy(*str + *i, c);
		*i += ft_strlen(c);
	}
	else if (mod == 1)
	{
		if (*i)
		{
			ft_putstr("\b");
			(*i)--;
		}
	}
	print_teil(buf);
	ft_strcpy(*str + *i, buf);
	(*str)[*i + ft_strlen(buf)] = '\0';
	free(buf);
}

int				handle_back_formard(char *c, int *i, size_t len)
{
	if (ft_strequ(c, "[D"))
	{
		if (*i)
		{
			ft_putstr("[D");
			(*i)--;
		}
		return (1);
	}
	if (ft_strequ(c, "[C"))
	{
		if (*i < len)
		{
			ft_putstr("[C");
			(*i)++;
		}
		return (1);
	}
	return (0);
}

int				handle_controls(char *c, int *i, char **str)
{
	if (ft_strequ(c, "\t"))
	{
		autocomplete(i, str);
		return (1);
	}
	else if (ft_strequ(c, "[A"))
	{
		ft_putstr("up");
		return (1);
	}
	else if (ft_strequ(c, "[B"))
	{
		ft_putstr("down");
		return (1);
	}
	return (0);
}
#include "minishell.h"

static void		check_size(char	*c, char **str)
{
	static int	n = 0;
	static int	rank = 1;
	char		*buf;

	n = **str ? ft_strlen(c) + n : ft_strlen(c);
	rank = **str ? rank : 1;
	if (n > BUFF_SIZE * rank)
	{
		while (n > BUFF_SIZE * rank)
			rank++;
		if ((buf = ft_strnew(BUFF_SIZE * rank)))
		{
			ft_strcpy(buf, *str);
			free(*str);
			*str = buf;
		}
		/*else
		{
			print_error("minishell", "memory error\n");
			exit_minishell(NULL);
		}*/
	}
}

void			back_carriage(char *str, int back, int prompt)
{
	int		index;
	int		len;

	len = ft_strlen(str);
	index = len - back;
	if (index < 0)
		index = 0;
	while (len > index)
		handle_back(&len, str, prompt);
}

/*void			print_str(char *str, int bback, int pback, int add)
{
	int		width;
	int		i;
	int		len;

	width = get_width();
	len = ft_wstrlen(str) - add;
	if (len % width == 0 && bback)
		ft_putstr("[A");
	while ((len - pback) / width < len / width)
	{
		pback -= width;
		ft_putstr("[B");
	}
	i = -1;
	ft_putstr("\r");
	while (++i < width)
		ft_putstr(" ");
	while (len > width)
	{
		len -= width;
		ft_putstr("[A");
	}
	ft_putstr("\r");
	ft_putstr(str);
	back_carriage(str, bback);
} */

static void		print_del(char *str, char *buf, int prompt)
{
	int		len[2];
	int		width;

	ft_putstr(buf);
	ft_putstr(" ");
	back_carriage(" ", 1, 0);
	len[0] = ft_wstrlen(str) + prompt;
	if (len[0] && len[0] % (width = get_width()) == 0)
	{
		len[1] = ft_wstrlen(buf);
		while (len[1] > width)
		{
			ft_putstr("[A");
			len[1] -= width;
		}
		if (ft_strlen(buf))
		{
			ft_putstr("[A");
			while (width - len[1]++)
				ft_putstr("[C");
		}
	}
	else
	{
		width = get_width();
		if (len[0] % width == width - 1)
			ft_putstr("[C");
		back_carriage(str, ft_strlen(buf), prompt);
	}
}

void			del_str(char *c, int *i, char **str, int prompt)
{
	char	*buf;
	int		mod;

	mod = (c[0] == 127 && !c[1]) ? 0 : 1;
	if (mod)
	{
		if (!ft_strlen(*str) || *i > ft_strlen(*str))
			return ;
		buf = ft_strdup(*str + *i + symbol_size((*str)[*i + 1]));
	}
	else
		buf = ft_strdup(*str + *i);
	if (!mod)
		handle_back(i, *str, prompt);
	ft_strcpy(*str + *i, buf);
	(*str)[*i + ft_strlen(buf)] = '\0';
	//(*str, ft_strlen(buf), ft_wstrlen(buf), -1);
	print_del(*str, buf, prompt);
	free(buf);
}

void			input_str(char *c, int *i, char **str, int prompt)
{
	char		*buf;

	check_size(c, str);
	if (ft_strequ("[3~", c) || (c[0] == 127 && !c[1]) || ft_strequ(c, ""))
		del_str(c, i, str, prompt);
	else
	{
		buf = ft_strdup(*str + *i);
		ft_strcpy(*str + *i, c);
		*i += ft_strlen(c);
		ft_strcpy(*str + *i, buf);
		(*str)[*i + ft_strlen(buf)] = '\0';
		ft_putstr(c);
		ft_putstr(buf);
		if (!((ft_wstrlen(*str) + prompt) % get_width()))
			ft_putstr("\n");
		back_carriage(*str, ft_strlen(buf), prompt);
		free(buf);
	}
}

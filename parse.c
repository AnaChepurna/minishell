#include "minishell.h"

static void		check_size(char	*c, char **str)
{
	static int	n = 0;
	static int	rank = 0;
	char		*buf;

	n = *str ? ft_strlen(c) + n : ft_strlen(c);
	rank = *str ? rank : 0;
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

void			back_carriage(char *str, int back)
{
	int		index;
	int		len;

	len = ft_strlen(str);
	index = len - back;
	while (len > index)
	{
		handle_back(&len, str);
	}
}

void			print_str(char *str, int bback, int pback, int add)
{
	int		width;
	int		i;
	int		len;

	width = get_width();
	len = ft_wstrlen(str) - add;
	if (len % width == 0 && add < 0 && bback)
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
}

void			del_str(char *c, int *i, char **str)
{
	char	*buf;
	int		mod;

	mod = ft_strequ("[3~", c) ? 1 : 0;
	if (mod)
		buf = *i <= ft_strlen(*str) ? ft_strdup(*str + *i + 1) : ft_strdup("");
	else
		buf = ft_strdup(*str + *i);
	if (!mod && *i)
	{
		(*i)--;
	}
	ft_strcpy(*str + *i, buf);
	(*str)[*i + ft_strlen(buf)] = '\0';
	print_str(*str, ft_strlen(buf), ft_wstrlen(buf), -1);
	free(buf);
}

void			input_str(char *c, int *i, char **str)
{
	char		*buf;

	check_size(c, str);
	if (ft_strequ("[3~", c) || (c[0] == 127 && !c[1]))
		del_str(c, i, str);
	else
	{
		buf = ft_strdup(*str + *i);
		ft_strcpy(*str + *i, c);
		*i += ft_strlen(c);
		ft_strcpy(*str + *i, buf);
		(*str)[*i + ft_strlen(buf)] = '\0';
		print_str(*str, ft_strlen(buf), ft_wstrlen(buf), ft_wstrlen(c));
		free(buf);
	}
}

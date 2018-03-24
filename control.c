#include "minishell.h"

void			handle_back(int *i, char *str)
{
	int		width;
	int		real_i;

	width = get_width();
	real_i = ft_wstrlen(str) - ft_wstrlen(str + *i);
	if (*i)
	{
		if (real_i % width == 0 && real_i != ft_wstrlen(str))
		{
			ft_putstr("[A");
			while (width--)
				ft_putstr("[C");
		}
		else
			ft_putstr("[D");
		(*i)--;
		while (str[*i] < 0 && !(str[*i] & 64))
			(*i)--;
	}
}

void			handle_forward(int *i, char *str)
{
	int		width;
	char	c;
	int		real_i;

	width = get_width();
	real_i = ft_wstrlen(str) - ft_wstrlen(str + *i);
	if (*i >= ft_strlen(str))
		return ;
	if (real_i % width == width - 1)
	{
		ft_putstr("[B");
		while (width--)
			ft_putstr("[D");
	}
	else
		ft_putstr("[C");
	if ((c = str[*i]) < 0)
		while (c < 0)
		{
			c = c << 1;
			(*i)++;
		}
	else
		(*i)++;
}

int				handle_back_forward(char *c, int *i, char *str)
{
	if (ft_strequ(c, "[D"))
	{
		handle_back(i, str);
		return (1);
	}
	if (ft_strequ(c, "[C"))
	{
		handle_forward(i, str);
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
#include "minishell.h"

static void		handle_back(int *i)
{
	int		width;

	width = get_width();
	if (*i)
	{
		if (*i % width == 0)
		{
			ft_putstr("[A");
			while (width--)
				ft_putstr("[C");
		}
		else
			ft_putstr("[D");
		(*i)--;
	}
}

static void		handle_forward(int *i, int len)
{
	int		width;

	width = get_width();
	if (*i < len)
	{
		if (*i % width == width - 1)
		{
			ft_putstr("[B");
			while (width--)
				ft_putstr("[D");
		}
		else
			ft_putstr("[C");
		(*i)++;
	}
}

int				handle_back_forward(char *c, int *i, int len)
{
	if (ft_strequ(c, "[D"))
	{
		handle_back(i);
		return (1);
	}
	if (ft_strequ(c, "[C"))
	{
		handle_forward(i, len);
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
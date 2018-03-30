#include "minishell.h"

void		clear_concole(int width, int real_len, int prompt)
{
	int		n;

	while (prompt > width)
		prompt -= width;
	while ((real_len + prompt) / width > 0)
	{
		ft_putstr("\r");
		n = 0;
		while (n++ < width)
			ft_putstr(" ");
		real_len -= width;
		ft_putstr("[A");
	}
	ft_putstr("\r");
	n = 0;
	while (n++ < prompt)
		ft_putstr("[C");
	while (n++ <= width)
		ft_putstr(" ");
	ft_putstr("\r");
	n = 0;
	while (n++ < prompt)
		ft_putstr("[C");
}

void		print_memcommand(char *command, char *old, int i, int prompt)
{
	int		real_len;
	int		width;

	width = get_width();
	real_len = ft_wstrlen(old);
	carriage_down(real_len, i, prompt);
	clear_concole(width, real_len, prompt);
	ft_putstr(command);
	if ((ft_wstrlen(command) + prompt) % width == 0)
		ft_putstr("\n");
}

void	carriage_down(int real_len, int i, int prompt)
{
	int width;

	width = get_width();
	prompt = prompt % width; 
	while ((real_len + prompt) / width >  (i + prompt) / width)
	{
		i += width;
		ft_putstr("[B");
	}
}

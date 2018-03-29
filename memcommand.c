#include "minishell.h"

void		add_command(char *command)
{
	t_list	*current;
	int		i;

	current = g_command;
	i = 0;
	while (current)
	{
		if (ft_strequ((char*)current->content, command))
		{
			current = ft_lstrm(&g_command, i);
			break;
		}
		i++;
		current = current->next;
	}
	if (!current)
		current = ft_lstnew(command, ft_strlen(command) + 1);
	ft_lstadd(&g_command, current);
}

char		*memcommand_manager(int mod, char *command)
{
	static t_list	*down = NULL;
	static t_list	*up = NULL;

	if (mod == ADD)
	{
		ft_lstdel(&down, &ft_memclr);
		ft_lstdel(&up, &ft_memclr);
		add_command(command);
		return (NULL);
	}
	if (mod == UP)
	{
		if (!down && !up)
			up = ft_lstmap(g_command, &copy_lst);
		if (up)
			ft_lstadd(&down, (ft_lstpop(&up)));
		return (down ? ft_strdup((char *)down->content) : NULL);
	}
	if (mod == DOWN)
	{
		if (down)
			ft_lstadd(&up, (ft_lstpop(&down)));
		return (down ? ft_strdup((char *)down->content) : ft_strnew(BUFF_SIZE + 1));
	}
	return (NULL);
}

void		clear_concole(int width, int real_len, int prompt)
{
	int		n;

	while (prompt > width)
	prompt -= width;
	while ((real_len + prompt) / width > prompt)
	{
		ft_putstr("[A\r");
		n = 0;
		while (n++ < width)
			ft_putstr(" ");
		real_len -= width;
	}
	ft_putstr("[A\r");
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
	ft_putstr("\n");
}
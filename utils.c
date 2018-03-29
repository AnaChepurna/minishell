#include "minishell.h"

int		check_dir(char **path, char **res_dir)
{
	int			i;
	int			isdir;
	char		*dir;
	struct stat	st;

	debug_home(path);
	i = ft_strlen(*path);
	isdir = 0;
	while (i >= 0 && (*path)[i] != '/')
		i--;
	dir = ft_strdup("./");
	if (i >= 0)
	{
		replace(&dir, ft_strsub(*path, 0, i + 1));
		if (!lstat(dir, &st) && st.st_mode & S_IFDIR)
			isdir = i + 1;
	}
	if (res_dir)
		*res_dir = dir;
	else
		free(dir);
	return (isdir);
}

int		symbol_size(char c)
{
	int	n;

	n = 1;
	if (c < 0)
	{
		while (c < 0)
		{
			c = c << 1;
			n++;
		}
	}
	return (n);
}

void				replace(char **dst, char *src)
{
	if (*dst)
		free(*dst);
	*dst = src;
}

int					get_width(void)
{
	struct winsize w;

	ioctl(0, TIOCGWINSZ, &w);
	return (w.ws_col);
}

t_list	*copy_lst(t_list *lst)
{
	t_list	*new;

	new = ft_lstnew(lst->content, lst->content_size);
	return (new);
}
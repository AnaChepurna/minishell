#include "minishell.h"

char	*get_overlap(t_list *lst)
{
	char	*mask;
	char	*content;
	int		i;

	mask = ft_strdup((char *)lst->content);
	lst = lst->next;
	while (lst)
	{
		content = (char *)lst->content;
		i = 0;
		while (mask[i] && content[i] && mask[i] == content[i])
			i++;
		mask[i] = '\0';
		lst = lst->next;
	}
	if (!ft_strlen(mask))
	{
		free(mask);
		return (NULL);
	}
	return (mask);
}

int		is_dir(char *path, char *name)
{
	struct stat		st;
	char			*file;

	file = ft_pathjoin(path, name);
	if (!lstat(file, &st) && st.st_mode & S_IFDIR)
	{
		free(file);
		return(1);
	}
	free(file);
	return (0);
}

int		full_file_list(t_list **lst, char *path, char *word, int n)
{
	DIR				*dir;
	struct dirent	*file;
	char			*fn;
	int				len;

	if ((dir = opendir(path)))
	{
		len = ft_strlen(word + n);
		while ((file = readdir(dir)))
		{
			fn = !is_dir(path, file->d_name) ?
			ft_strdup(file->d_name) : ft_strjoin(file->d_name, "/");
			if (ft_strnequ(word + n, fn, len) && !ft_strequ(word + n, fn))
				ft_lstadd(lst, ft_lstnew(fn + len, ft_strlen(fn + len) + 1));
			free(fn);
		}
		closedir(dir);
	}
	if (!(*lst))
		return (0);
	return (1);
}

int		full_dir_list(t_list **lst, char *path, char *word, int n)
{
	DIR				*dir;
	struct dirent	*file;
	char			*fn;
	int				len;

	if ((dir = opendir(path)))
	{
		len = ft_strlen(word + n);
		while ((file = readdir(dir)))
		{
			if (is_dir(path, file->d_name))
			{
			fn = ft_strjoin(file->d_name, "/");
			if (ft_strnequ(word + n, fn, len) && !ft_strequ(word + n, fn))
				ft_lstadd(lst, ft_lstnew(fn + len, ft_strlen(fn + len) + 1));
			free(fn);
			}
		}
		closedir(dir);
	}
	if (!(*lst))
		return (0);
	return (1);
}

int		full_bin_list(t_list **lst, char *path, char *word, int n)
{
	DIR				*dir;
	struct dirent	*file;
	char			*fn;
	int				len;

	if (n == ft_strlen(word))
		return (0);
	if ((dir = opendir(path)))
	{
		len = ft_strlen(word + n);
		while ((file = readdir(dir)))
		{
			fn = ft_pathjoin(path, file->d_name);
			if (is_bin(fn, 0) == 1 && (ft_strnequ(word + n, file->d_name, len) &&
					!ft_strequ(word + n, file->d_name)))
				ft_lstadd(lst, ft_lstnew(file->d_name + len,
					ft_strlen(file->d_name + len) + 1));
			free(fn);
		}
		closedir(dir);
	}
	if (!(*lst))
		return (0);
	return (1);
}
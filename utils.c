#include "minishell.h"

int		check_dir(char *path, char **res_dir)
{
	int			i;
	int			isdir;
	char		*dir;
	struct stat	st;

	i = ft_strlen(path);
	isdir = 0;
	while (i >= 0 && path[i] != '/')
		i--;
	dir = ft_strdup("./");
	if (i >= 0)
	{
		free(dir);
		dir = ft_strsub(path, 0, i + 1);
		if (!lstat(dir, &st) && st.st_mode & S_IFDIR)
			isdir = i + 1;
	}
	if (res_dir)
		*res_dir = dir;
	else
		free(dir);
	return (isdir);
}
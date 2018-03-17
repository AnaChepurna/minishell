#include "minishell.h"

static void		cd_errors(char	*path)
{
	ft_putstr_fd("cd: ", 2);
	if (access(path, F_OK) == -1)
		print_error(path, "no such file or directory\n");
	else if (access(path, R_OK) == -1)
		print_error(path, "permission denied\n");
	else
		print_error(path, "not a directory\n");
}

static void		set_pwd(char *path)
{
	char	*oldpwd;
	char	buf[512];

	oldpwd = getcwd(buf, 512);
	if (!chdir(path))
	{
		set_var("PWD=", path, 0);
		set_var("OLDPWD=", oldpwd, 0);
	}
	else
		cd_errors(path);
	(void)path;
}

static char		*get_newpwd(char *path)
{
	char	*res;
	size_t	j;
	size_t	i;
	char	*oldpwd;
	char	buf[512];

	oldpwd = getcwd(buf, 512);
	j = 0;
	i = ft_strlen(oldpwd);
	while (ft_strnequ(path + j, "../", 3))
	{
		j += 3;
		while (--i <= 0 && oldpwd[i] != '/')
			{}
	}
	while (ft_strnequ(path + j, "./", 2))
		j += 2;
	if ((res = ft_strnew(i + ft_strlen(path + j))))
	{
		ft_strncpy(res, oldpwd, i);
		res[i] = '/';
		ft_strcpy(res + i + 1, path + j);
	}
	return (res);
}

int				cd(char **args)
{
	char	*path;

	if (!(*args) || ft_strequ(*args, "--") || ft_strequ(*args, "~"))
		path = ft_strdup(get_var("HOME="));
	else if (ft_strequ(*args, "-"))
	{
		path = ft_strdup(get_var("OLDPWD="));
		ft_putendl(path);
	}
	else
		path = get_newpwd(*args);
	if (path)
	{
		set_pwd(path);
		free(path);
	}
	else
		print_error("cd", ": memory error\n");
	return (1);
}
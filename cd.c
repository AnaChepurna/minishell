#include "minishell.h"

static void		cd_errors(char	*path)
{
	char	*error_name;

	error_name = ft_strjoin ("cd: ", path);
	if (access(path, F_OK) == -1)
		print_error(error_name, "no such file or directory\n");
	else if (access(path, R_OK) == -1)
		print_error(error_name, "permission denied\n");
	else
		print_error(error_name, "not a directory\n");
	free(error_name);
}

static void		set_pwd(char *path, char *oldpwd)
{
	char	*newpwd;
	char	buf[512];

	if (!chdir(path))
	{
		newpwd = getcwd(buf, 512);
		set_var("PWD=", newpwd, 0);
		set_var("OLDPWD=", oldpwd, 0);
	}
	else
		cd_errors(path);
}

static char		*get_pwd(char *path, char *oldpwd)
{
	char	*buf;
	char	*newpwd;

	if (!path || ft_strequ(path, "--") || ft_strequ(path, "~"))
		newpwd = ft_strdup(get_var("HOME="));
	else if (ft_strequ(path, "-"))
	{
		newpwd = ft_strdup(get_var("OLDPWD="));
		ft_putendl(newpwd);
	}
	else if (ft_strnequ(path, "/", 1))
		newpwd = ft_strdup(path);
	else
	{
		if (ft_strnequ(path, "~", 1))
		{
			buf = ft_strdup(get_var("HOME="));
			path += 2;
		}
		else
			buf = ft_strdup(oldpwd);
		newpwd = ft_pathjoin(buf, path);
		free(buf);
	}
	return (newpwd);
}

int				cd(char **args)
{
	char	*path;
	char	*oldpwd;
	char	buf[512];

	oldpwd = getcwd(buf, 512);
	path = get_pwd(*args, oldpwd);
	if (path)
	{
		set_pwd(path, oldpwd);
		free(path);
	}
	else
		print_error("cd", ": memory error\n");
	return (1);
}
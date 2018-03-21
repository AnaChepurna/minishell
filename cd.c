/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achepurn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 21:46:42 by achepurn          #+#    #+#             */
/*   Updated: 2018/03/21 21:46:44 by achepurn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void				set_pwd(char *path, char *oldpwd, int p)
{
	char	*error_name;
	char	*newpwd;
	char	buf[512];

	if (!chdir(path))
	{
		newpwd = p ? getcwd(buf, 512) : path;
		set_var("PWD", newpwd, 0);
		set_var("OLDPWD", oldpwd, 0);
	}
	else
	{
		error_name = ft_strjoin("cd: ", path);
		if (access(path, F_OK) == -1)
			print_error(error_name, "no such file or directory\n");
		else if (access(path, R_OK) == -1)
			print_error(error_name, "permission denied\n");
		else
			print_error(error_name, "not a directory\n");
		free(error_name);
	}
}

static void			format_path(char **pwd)
{
	char	*line;
	char	*ptr;
	int		minus;

	minus = 0;
	if ((ptr = ft_strstr(*pwd, "../")) ||
			((ptr = ft_strstr(*pwd, "/..")) && !ptr[3] && ptr != *pwd))
	{
		minus = 4;
		while (--ptr > *pwd && *(ptr - 1) != '/')
			minus++;
	}
	else if ((ptr = ft_strstr(*pwd, "./")) ||
		((ptr = ft_strstr(*pwd, "/.")) && !ptr[2] && ptr != *pwd))
		minus = 2;
	else if ((ptr = ft_strstr(*pwd, "/.")) && !ptr[2] && ptr == *pwd)
	{
		minus = 1;
		ptr++;
	}
	else if ((ptr = ft_strstr(*pwd, "//")) ||
			((ptr = ft_strrchr(*pwd, '/')) && !ptr[1] && ptr != *pwd))
		minus = 1;
	if (minus && (line = ft_strnew(ft_strlen(*pwd) - minus)))
	{
		ft_strncpy(line, *pwd, ptr - *pwd);
		ft_strcpy(line + (ptr - *pwd), ptr + minus);
		free(*pwd);
		*pwd = line;
		format_path(pwd);
	}
}

static char			*get_pwd(char *path, char *oldpwd)
{
	char	*buf;
	char	*newpwd;

	if (!path || ft_strequ(path, "--") || ft_strequ(path, "~"))
		newpwd = ft_strdup(get_var(g_env, "HOME="));
	else if (ft_strequ(path, "-"))
	{
		newpwd = ft_strdup(get_var(g_env, "OLDPWD="));
		ft_putendl(newpwd);
	}
	else if (ft_strnequ(path, "/", 1))
		newpwd = ft_strdup(path);
	else
	{
		if (ft_strnequ(path, "~", 1))
		{
			buf = ft_strdup(get_var(g_env, "HOME="));
			path += 2;
		}
		else
			buf = ft_strdup(oldpwd);
		newpwd = ft_pathjoin(buf, path);
		free(buf);
	}
	return (newpwd);
}

int					cd(char **args)
{
	char	*path;
	char	*oldpwd;
	int		p;

	p = 0;
	if (ft_strequ(*args, "-P"))
	{
		p = 1;
		args++;
	}
	oldpwd = ft_strdup(get_var(g_env, "PWD="));
	path = get_pwd(*args, oldpwd);
	if (path)
	{
		if (!p)
			format_path(&path);
		if (!ft_strequ(path, oldpwd))
			set_pwd(path, oldpwd, p);
		free(path);
	}
	else
		print_error("cd", ": memory error\n");
	free(oldpwd);
	return (1);
}

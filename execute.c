/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achepurn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 21:47:16 by achepurn          #+#    #+#             */
/*   Updated: 2018/03/21 21:47:18 by achepurn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			run(char *path, char **args, t_list *local_env)
{
	pid_t	pid;
	char	**env;
	int		status;
	int		ret;

	status = 1;
	ret = 0;
	env = ft_lsttoarr(local_env);
	if (!(pid = fork()))
	{
		if ((ret = execve(path, args, env)))
		{
			print_error("minishell", "cannot run a proccess\n");
			exit(1);
		}
	}
	else if (pid < 0)
		status = 0;
	signal(SIGINT, sigint_fork_handler);
	wait(&pid);
	g_status = pid >> 8;
	ft_arrfree(&env);
	return (status);
}

int			is_bin(char *path, int check_dir)
{
	struct stat st;
	char		*dir;
	int			i;
	int			isdir;

	i = (int)ft_strlen(path);
	isdir = 0;
	if (check_dir)
	{
		while (i >= 0 && path[i] != '/')
			i--;
		if (i >= 0)
		{
			dir = ft_strsub(path, 0, i);
			if (!lstat(dir, &st) && st.st_mode & S_IFDIR)
				isdir = 1;
			free(dir);
		}
	}
	if (!lstat(path, &st) && st.st_mode & S_IFREG && st.st_mode & S_IXUSR)
		return (1);
	if (isdir)
		print_error(path, "no such file or directory\n");
	return (isdir ? 2 : 0);
}

int			exec_bin(char **args, t_list *env)
{
	char		**paths;
	char		*name;
	size_t		i;
	int			status;

	name = (ft_strequ(*args, "ls") && !get_var(env, "PATH=")) ?
	ft_strdup("/bin/ls") : ft_strdup(*args);
	if (!(status = is_bin(name, 1)))
	{
		if ((paths = ft_strsplit(get_var(env, "PATH="), ':')))
		{
			i = -1;
			while (paths[++i])
			{
				free(name);
				name = ft_pathjoin(paths[i], *args);
				if ((status = is_bin(name, 0)))
					break ;
			}
			ft_arrfree(&paths);
		}
	}
	status = (status == 1) ? run(name, args, env) : status;
	free(name);
	return (status);
}

static int	exec_builtin(char **args)
{
	if (ft_strequ(args[0], "exit"))
		return (exit_minishell(args + 1));
	if (ft_strequ(args[0], "env"))
		return (env(args + 1));
	if (ft_strequ(args[0], "echo"))
		return (echo(args + 1));
	if (ft_strequ(args[0], "cd"))
		return (cd(args + 1));
	if (ft_strequ(args[0], "setenv"))
		return (set_var(args[1], args[2], 1));
	if (ft_strequ(args[0], "unsetenv"))
	{
		while (*(++args))
			unset_var(*args, 1);
		return (1);
	}
	if (ft_strequ(args[0], "undoenv"))
		return (undo_var(args[1]));
	if (ft_strequ(args[0], "resetenv"))
		return (reset_env());
	return (0);
}

void		execute(char *command)
{
	char	**args;
	size_t	i;

	args = ft_strsplitmq(command, " \t");
	i = 0;
	while (args[i])
	{
		debug_home(&(args[i]));
		delete_quotes(&(args[i]));
		debug_eof(&(args[i]));
		i++;
	}
	if (*args)
	{
		if (!(exec_builtin(args) || exec_bin(args, g_env)))
			print_error(args[0], "command not found\n");
	}
	ft_arrfree(&args);
}

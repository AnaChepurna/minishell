#include "minishell.h"

static int	run(char *path, char **args)
{
	pid_t	pid;
	char	**env;
	int		status;

	status = 1;
	env = ft_lsttoarr(g_env);
	if (!(pid = fork()))
	{
		execve(path, args, env);
	}
	else if (pid < 0)
		status = 0;
	signal(SIGINT, sigint_fork_handler);
	wait(&pid);
	ft_arrfree(&env);
	return (status);
}

static int	is_bin(char *path, int	check_dir)
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

static int	exec_bin(char **args)
{
	char		**paths;
	char		*name;
	size_t		i;
	int			status;

	name = ft_strdup(*args);
	if (!(status = is_bin(name, 1)))
	{
		if ((paths = ft_strsplit(get_var("PATH="), ':')))
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
	if (status == 1)
		status = run(name, args);
	free(name);
	return (status);
}

static int	exec_builtin(char **args)
{
	if (ft_strequ(args[0], "exit"))
	{
		clear_global();
		exit(1);
	}
	if (ft_strequ(args[0], "env"))
		return (print_env());
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
	if (ft_strequ(args[0], "help"))
		return (help());
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
	if (!(exec_builtin(args) || exec_bin(args)))
		print_error(args[0], "command not found\n");
	ft_arrfree(&args);
}

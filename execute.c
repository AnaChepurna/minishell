#include "minishell.h"

static int	run(char *path, char **args)
{
	pid_t	pid;
	char	**env;
	int		status;

	status = 1;
	env = ft_lsttoarr(g_env);
	if (!(pid = fork()))
		execve(path, args, env);
	else if (pid < 0)
		status = 0;
	wait(&pid);
	ft_arrfree(&env);
	return (status);
}

static int	is_bin(char *path)
{
	struct stat st;

	if (!lstat(path, &st))
	{
		if (st.st_mode & S_IFREG && st.st_mode & S_IXUSR)
			return (1);
	}
	return (0);
}

static int	exec_bin(char **args)
{
	char		**paths;
	char		*name;
	size_t		i;
	int			status;

	name = ft_strdup(*args);
	if (!(status = is_bin(name)))
	{
		paths = ft_strsplit(get_var("PATH="), ':');
		i = -1;
		while (paths[++i])
		{
			free(name);
			name = ft_pathjoin(paths[i], *args);
			if ((status = is_bin(name)))
				break ;
		}
		ft_arrfree(&paths);
	}
	if (status)
		status = run(name, args);
	free(name);
	return (status);
}

static int	exec_builtin(char **args)
{
	if (ft_strequ(args[0], "exit"))
		exit_minishell();
	if (ft_strequ(args[0], "env"))
		return (print_env());
	if (ft_strequ(args[0], "echo"))
		return (echo(args + 1));
	if (ft_strequ(args[0], "cd"))
		return (cd(args + 1));
	return (0);
}

void		execute(char *command)
{
	char	**args;

	args = ft_strsplitm(command, " \t");
	if (!(exec_builtin(args) || exec_bin(args)))
		print_error(args[0], ": command not found\n");
	ft_arrfree(&args);
}
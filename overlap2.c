#include "minishell.h"

static void	add_builtin(t_list **lst, char *word, char *name, int len)
{
	if (ft_strnequ(word, name, len) && ft_strnequ(word, name, len))
		ft_lstadd(lst, ft_lstnew(name + len, ft_strlen(name + len) + 1));
}

static void	add_commands(t_list **lst, char *word, int len)
{
	add_builtin(lst, word, "cd", len);
	add_builtin(lst, word, "echo", len);
	add_builtin(lst, word, "env", len);
	add_builtin(lst, word, "exit", len);
	add_builtin(lst, word, "echo", len);
	add_builtin(lst, word, "reset", len);
	add_builtin(lst, word, "setenv", len);
	add_builtin(lst, word, "unsetenv", len);
	add_builtin(lst, word, "undoenv", len);
	add_builtin(lst, word, "ls", len);
	add_builtin(lst, word, "emacs", len);
	add_builtin(lst, word, "vim", len);
}

int			full_command_list(t_list **lst, char *word)
{
	int 		len;
	char		*path_var;
	char		**paths;
	int			i;

	len = ft_strlen(word);
	if ((paths = ft_strsplit(get_var(g_env, "PATH="), ':')))
	{
		i = 0;
		while(paths[i])
			full_bin_list(lst, paths[i++], word, 0);
		ft_arrfree(&paths);
	}
	add_commands(lst, word, len);
	if ((paths = ft_strsplit(get_var(g_env, "USER_COMMAND="), ':')))
	{
		i = -1;
		while(paths[++i])
		{
			if (ft_strnequ(word, paths[i], len) && !ft_strequ(word, paths[i]))
				ft_lstadd(lst, ft_lstnew(paths[i] + len, ft_strlen(paths[i] + len) + 1));
		}
		ft_arrfree(&paths);
	}
	return (*lst ? 1 : 0);
}

int		full_var_list(t_list **lst, char *word)
{
	t_list	*env;
	char	*var;
	char	*res;
	char	*ptr;
	int		len;

	if (ft_strchr(word, '='))
		return (0);
	word++;
	env = g_env;
	len = ft_strlen(word);
	while (env)
	{
		var = (char *)env->content;
		if (ft_strnequ(word, var, len) && (ptr = ft_strchr(var, '=')))
		{
			res = ft_strsub(var, len, ptr - var - len);
			ft_lstadd(lst, ft_lstnew(res, ft_strlen(res) + 1));
			free(res);
		}
		env = env->next;
	}
	if (!(*lst))
		return (0);
	return (1);
}

char	*get_var(t_list *env, char *var_name)
{
	t_list	*lst;
	size_t	len;
	char	*var;

	lst = env;
	var = !ft_strchr(var_name, '=') ?
	ft_strjoin(var_name, "=") : ft_strdup(var_name);
	len = ft_strlen(var_name);
	while (lst)
	{
		if (ft_strnequ(var_name, (char *)lst->content, len))
		{
			free(var);
			return ((char *)lst->content + len);
		}
		lst = lst->next;
	}
	free(var);
	return (NULL);
}
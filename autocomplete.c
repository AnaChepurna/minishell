#include "minishell.h"


int		word_number(char *str, int i, char **ptr)
{
	int		j;

	*ptr = NULL;
	j = i - 1;
	if (!i || IS_SPACE(str[j]) || str[j] == ';')
		return (0);
	while (j >= 0 && !(IS_SPACE(str[j])))
		j--;
	*ptr = ft_strsub(str, j + 1, i - j);
	while (j >= 0 && IS_SPACE(str[j]))
		j--;
	if (j >= 0 && str[j] != ';')
		return(2);
	return (1);
}

int			is_bin(char *path, int check)
{
	int			isdir;
	struct stat	st;

	isdir = 0;
	if (check)
		isdir = check_dir(path, NULL);
	if (!lstat(path, &st) && st.st_mode & S_IFREG && st.st_mode & S_IXUSR)
		return (1);
	//if (isdir)
		//print_error(path, "no such file or directory\n");
	return (isdir ? 2 : 0);
}

void	complete_command(char *word, int *i, char **str, int prompt)
{
	t_list 			*lst;
	t_list			*l;
	char			*path;
	char			*res;
	int				n;

	lst = NULL;
	if (full_command_list(&lst, word))
		input_str((char *)lst->content, i, str, prompt);
	else if ((n = check_dir(word, &path)) && full_file_list(&lst, path, word, n)
		&& (res = get_overlap(lst)))
	{
		input_str(res, i, str, prompt);
		free(res);
	}
	free(path);
	ft_lstdel(&lst, &ft_memclr);
}

void	complete_file(char *word, int *i, char **str, int prompt)
{
	char			*res[2];
	char			*path;
	struct stat		st;
	int				n;
	t_list			*lst;

	lst = NULL;
	res[0] = NULL;
	if (((n = check_dir(word, &path)) || ft_strequ(path, "./"))
		&& full_file_list(&lst, path, word, n) && (res[0] = get_overlap(lst)))
	{
		res[1] = ft_strjoin(word, res[0]);
		if (!lstat(res[1], &st) && st.st_mode & S_IFDIR)
		{
			free(res[1]);
			res[1] = res[0];
			res[0] = ft_strjoin(res[1], "/");
		}
		free(res[1]);
		input_str(res[0], i, str, prompt);
	}
	if (res[0])
		free(res[0]);
	ft_lstdel(&lst, &ft_memclr);
	free(path);
}

void	complete_var(char *word, int *i, char **str, int prompt)
{
	t_list *lst;
	char	*res;

	lst = NULL;
	if (full_var_list(&lst, word) && (res = get_overlap(lst)))
	{
		input_str(res, i, str, prompt);
		free(res);
	}
	ft_lstdel(&lst, &ft_memclr);
}

void	autocomplete(int *i, char **str, int prompt)
{
	int		n;
	char	*ptr;

	n = word_number(*str, *i, &ptr);
	if (!n)
		return ;
	if (*ptr == '$')
		complete_var(ptr, i, str, prompt);
	else if (n == 1)
		complete_command(ptr, i, str, prompt);
	else if (n == 2)
		complete_file(ptr, i, str, prompt);
	free(ptr);
}
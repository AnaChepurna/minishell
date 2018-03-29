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

void	complete_command(char *arg_word, int *i, char **str, int prompt)
{
	t_list 			*lst;
	char			*path;
	char			*word;
	int				n;

	lst = NULL;
	path = NULL;
	word = ft_strdup(arg_word);
	if (full_command_list(&lst, word))
		input_str((char *)lst->content, i, str, prompt);
	else if ((n = check_dir(&word, &path)) && full_bin_list(&lst, path, word, n))
		input_str((char *)lst->content, i, str, prompt);
	else
		complete_file(word, i, str, prompt);
	if (path)
		free(path);
	free(word);
	ft_lstdel(&lst, &ft_memclr); 
}

void	complete_file(char *arg_word, int *i, char **str, int prompt)
{
	char			*res;
	char			*word;
	char			*path;
	int				n;
	t_list			*lst;

	lst = NULL;
	word = ft_strdup(arg_word);
	if (((n = check_dir(&word, &path)) || ft_strequ(path, "./"))
		&& full_file_list(&lst, path, word, n) && (res = get_overlap(lst)))
	{
		input_str(res, i, str, prompt);
		free(res);
	}
	ft_lstdel(&lst, &ft_memclr);
	free(word);
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
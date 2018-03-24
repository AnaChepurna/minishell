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

void	complete_command(char *ptr, int *i, char **str)
{
	printf("complete_command\n");
}

void	complete_file(char *ptr, int *i, char **str)
{
	char			*path;
	DIR				*dir;
	struct dirent	*file;
	int				n;
	size_t			len;

	if ((n = check_dir(ptr, &path)) || ft_strequ(path, "./"))
	{
		if (!(dir = opendir(path)))
			return ;
		len = ft_strlen(ptr + n);
		while (len && (file = readdir(dir)))
		{
			if (ft_strnequ(ptr + n, file->d_name, len) &&
				!ft_strequ(ptr + n, file->d_name))
			{
				input_str(file->d_name + len, i, str);
				break;
			}
		}
		closedir(dir);
	}
	free(path);
}

void	complete_var(char *ptr, int *i, char **str)
{
	printf("complete_var\n");
}

void	autocomplete(int *i, char **str)
{
	int		n;
	char	*ptr;

	n = word_number(*str, *i, &ptr);
	if (!n)
		return ;
	if (*ptr == '$')
		complete_var(ptr, i, str);
	else if (n == 1)
		complete_command(ptr, i, str);
	else if (n == 2)
		complete_file(ptr, i, str);
	free(ptr);
}
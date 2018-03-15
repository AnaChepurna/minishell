#include "minishell.h"

char	*get_var(char *var_name)
{
	t_list	*lst;
	size_t	len;

	lst = g_env;
	len = ft_strlen(var_name);
	while (lst)
	{
		if (ft_strnequ(var_name, (char *)lst->content, len))
			return ((char *)lst->content + len);
		lst = lst->next;
	}
	return (NULL);
}
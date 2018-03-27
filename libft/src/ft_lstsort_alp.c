#include "libft.h"

t_list	*ft_lstsort_alp(t_list **begin)
{
	t_list *lst;

	lst = *begin;
	while (lst && lst->next)
	{
		if (ft_strcmp((char *)lst->content, (char *)lst->next->content) > 0)
		{
			ft_putstr((char *)lst->content);
			ft_putstr(" -> ");
			ft_putendl((char *)lst->next->content);
			ft_swap(&(lst->content), &(lst->next->content));
			return (ft_lstsort_alp(begin));
		}
		lst = lst->next;
	}
	return (*begin);
}
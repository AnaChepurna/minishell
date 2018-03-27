#include <stdio.h>

int main()
{
	printf("KO\n");
}

void	foreach(t_list *begin,  void (*f)(void *))
{
	t_list	*lst;

	lst = begin;
	while(lst)
	{
		(*f)(lst->content);
		lst = next->lst;
	}
}
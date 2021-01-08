#include "minishell.h"

t_listdir	*new_maillon(t_listdir *actual, char *name)
{
	t_listdir *list;

	list = malloc(sizeof(t_listdir));
	list->name = name;
	list->next = actual;
	return (list);
}

void		free_list(t_listdir *a)
{
	if (a)
	{
		free_list(a->next);
		free(a->name);
		free(a);
	}
}

void		sort_list(t_listdir *actual)
{
	t_listdir	*a;
	t_listdir	*b;
	char		*tmp;

	if (!actual || !actual->next)
		return ;
	a = actual;
	while (a)
	{
		b = a->next;
		while (b)
		{
			if (ft_strcmp1(a->name, b->name) > 0)
			{
				tmp = a->name;
				a->name = b->name;
				b->name = tmp;
			}
			b = b->next;
		}
		a = a->next;
	}
}

void		sort_list_dsm(t_listdir *actual)
{
	t_listdir	*a;
	t_listdir	*b;
	char		*tmp;

	if (!actual || !actual->next)
		return ;
	a = actual;
	while (a)
	{
		b = a->next;
		while (b)
		{
			if (ft_strcmp2(a->name, b->name) > 0)
			{
				tmp = a->name;
				a->name = b->name;
				b->name = tmp;
			}
			b = b->next;
		}
		a = a->next;
	}
}

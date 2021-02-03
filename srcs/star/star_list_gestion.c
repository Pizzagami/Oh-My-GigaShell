/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   star_list_gestion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braimbau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 15:26:13 by braimbau          #+#    #+#             */
/*   Updated: 2021/02/03 10:28:45 by braimbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

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

t_token		*starize_list(t_token *first, t_token *max, char *home)
{
	t_token	*a;

	a = first;
	while (a && a != max)
	{
		if (a == first && srcchar(CSTAR, a->str) != -1)
		{
			a = first_link(a, home, first);
		}
		else if (a->next && a->next != max && srcchar(CSTAR, a->next->str) != -1)
		{
			a = other_links(a, home);
		}
		if (a && a != max)
		{
			a = a->next;
		}
	}
	return (first);
}

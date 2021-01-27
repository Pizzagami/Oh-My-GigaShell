/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   star_some_stuff.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braimbau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 14:46:25 by braimbau          #+#    #+#             */
/*   Updated: 2021/01/08 15:27:44 by braimbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

int			recursive(char *str, char *patern, int rc, t_mx x)
{
	int i;

	if (x.s == 0 && x.p == 0 && str[x.s] == '.' && str[x.s] != patern[x.p])
		return (0);
	if (!str[x.s] && (!patern[x.p] || rc == 0))
		return (1);
	else if (!str[x.s])
		return (0);
	if (patern[x.p] != CSTAR)
	{
		if (str[x.s] == patern[x.p])
			return (recursive(str, patern, rc, init_mx(x.p + 1, x.s + 1)));
		else
			return (0);
	}
	i = rc;
	while (i > -1)
	{
		if (recursive(str, patern, rc - i, init_mx(x.p + 1, x.s + i)))
			return (1);
		i--;
	}
	return (0);
}

void		add_list(t_listdir *actual, char *minipath, char **final)
{
	char *pathedname;
	char *tmp;

	while (actual)
	{
		if (minipath)
			pathedname = ft_strjoin_sep(minipath, actual->name, '/');
		else
			pathedname = ft_strdup(actual->name);
		tmp = *final;
		if (*final == NULL)
			*final = pathedname;
		else
		{
			*final = ft_strjoin_sep(*final, pathedname, ' ');
			free(pathedname);
		}
		free(tmp);
		actual = actual->next;
	}
}

int			add_matching_names(char *path, int sfdo, t_listdir **actual,
								char *patern)
{
	DIR				*dir;
	t_listdir		*list;
	struct dirent	*dirent;

	dir = opendir(path);
	if (dir == NULL)
		return (1);
	while ((dirent = readdir(dir)) != NULL)
	{
		if (superstar(dirent->d_name, patern) && (!sfdo ||
			is_dir(path, dirent->d_name)))
		{
			list = malloc(sizeof(t_list));
			if (sfdo)
				list->name = ft_strjoin_sep(dirent->d_name, NULL, '/');
			else
				list->name = ft_strdup(dirent->d_name);
			list->next = (*actual);
			*actual = list;
		}
	}
	closedir(dir);
	return (0);
}

t_token		*first_link(t_token *a, char *home, t_token *first)
{
	char	*str;
	t_token	*tmp;
	t_token	*tmp2;

	str = NULL;
	gigastar(a->str, &str, home);
	tmp = create_simple_token_list(str);
	tmp2 = tmp;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = a->next;
	free(first->str);
	free(first);
	first = tmp2;
	a = first;
	free(str);
	return (a);
}

t_token		*other_links(t_token *a, char *home)
{
	char	*str;
	t_token	*tmp;
	t_token	*tmp2;

	str = NULL;
	gigastar(a->next->str, &str, home);
	tmp = create_simple_token_list(str);
	tmp2 = tmp;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = a->next->next;
	free(a->next->str);
	free(a->next);
	a->next = tmp2;
	free(str);
	return (a);
}

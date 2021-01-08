/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   star.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braimbau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 10:30:03 by braimbau          #+#    #+#             */
/*   Updated: 2021/01/08 13:14:51 by braimbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "token.h"
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>

int			is_dir(char *path, char *file)
{
	struct stat buf;

	path = ft_strjoin_sep(path, file, '/');
	stat(path, &buf);
	free(path);
	if (S_ISDIR(buf.st_mode))
		return (1);
	return (0);
}

void		removedoublestars(char **str_p)
{
	char	*str;
	int		x;

	str = *str_p;
	x = 0;
	while (str && str[x] && str[x + 1])
	{
		if (str[x] == CSTAR && str[x + 1] == CSTAR)
			removechar(str_p, x + 1);
		else
			x++;
	}
}

int			numberstars(char *str)
{
	int x;
	int y;

	x = 0;
	y = 0;
	while (str && str[x])
	{
			if (str[x] == CSTAR)
			y++;
		x++;
	}
	return (y);
}

t_mx		init_mx(int p, int s)
{
	t_mx	x;

	x.s = s;
	x.p = p;
	return (x);
}

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

int			superstar(char *str, char *patern)
{
	int rc;
	int ret;

	removedoublestars(&patern);
	rc = strlen(str) - (strlen(patern) - numberstars(patern));
	ret = recursive(str, patern, rc, init_mx(0, 0));
	return (ret);
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
					is_dir(path, dirent->d_name))){
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

int			megastar(char *patern, char *path, char *minipath, char **final)
{
	t_listdir		*actual;
	int				sfdo;

	sfdo = 0;
	if (srcchar('/', patern) != -1)
	{
		sfdo = 1;
		patern[ft_strlen(patern) - 1] = 0;
	}
	actual = NULL;
	if (add_matching_names(path, sfdo, &actual, patern))
		return (1);
	sort_list(actual);
	add_list(actual, minipath, final);
	free_list(actual);
	return (0);
}

void		throughdir(char *mpath, char *patern, t_listdir *a, char **final)
{
	char *path;
	char *newminipath;
	char *newpatern;
	char *newpath;

	path = mpath + ft_strlen(mpath) + 1;
	while (a)
	{
		newpatern = ft_substr(patern, srcchar('/', patern) + 1,
		ft_strlen(patern) - srcchar('/', patern) + 1);
		newpath = ft_strjoin_sep(path, a->name, '/');
		if (mpath[0])
		{
			newminipath = ft_strjoin_sep(mpath, a->name, '/');
			recurdir(newpatern, newpath, newminipath, final);
			free(newminipath);
		}
		else
			recurdir(newpatern, newpath, a->name, final);
		mfree(newpatern, newpath);
		a = a->next;
	}
	free(mpath);
}

int			recurdir(char *patern, char *path, char *minipath, char **final)
{
	DIR				*dir;
	struct dirent	*dirent;
	char			*dirname;
	t_listdir		*actual;

	actual = NULL;
	if (srcchar('/', patern) == -1
		|| srcchar('/', patern) == (int)ft_strlen(patern) - 1)
	{
		if (patern[0] != '/')
			return (megastar(patern, path, minipath, final));
		return (megastar("\x01", "/", minipath, final));
	}
	if ((dir = opendir(path)) == NULL)
		return (1);
	dirname = ft_substr(patern, 0, srcchar('/', patern));
	while ((dirent = readdir(dir)) != NULL)
		if (is_dir(path, dirent->d_name) && superstar(dirent->d_name, dirname))
			actual = new_maillon(actual, ft_strdup(dirent->d_name));
	sort_list_dsm(actual);
	throughdir(ft_strjoin_sep(minipath, path, '\0'), patern, actual, final);
	free_list(actual);
	free(dirname);
	closedir(dir);
	return (0);
}

int			gigastar(char *patern, char **final, char *home)
{
	char *path;
	char *minipath;

	*final = NULL;
	if (patern[0] == '/')
		recurdir(patern + 1, "/", "", final);
	else if (patern[0] == '~')
		recurdir(patern + 2, home, home, final);
	else
	{
		minipath = NULL;
		path = malloc(sizeof(char) * 500);
		getcwd(path, 500);
		recurdir(patern, path, minipath, final);
		free(path);
	}
	if (!(*final))
	{
		dereplace_stars(patern);
		*final = ft_strdup(patern);
	}
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

t_token		*starize_list(t_token *first, t_token *max, char *home)
{
	t_token	*a;

	a = first;
	while (a && a != max)
	{
		if (a == first && srcchar(CSTAR, a->str) != -1)
			a = first_link(a, home, first);
		if (a->next && a->next != max && srcchar(CSTAR, a->next->str) != -1)
			a = other_links(a, home);
		if (a && a != max)
			a = a->next;
	}
	return (first);
}

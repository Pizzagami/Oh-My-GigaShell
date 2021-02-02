/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   star.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braimbau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 10:30:03 by braimbau          #+#    #+#             */
/*   Updated: 2021/02/02 14:22:37 by braimbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "token.h"
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>

int			superstar(char *str, char *patern)
{
	int rc;
	int ret;

	removedoublestars(&patern);
	rc = strlen(str) - (strlen(patern) - numberstars(patern));
	ret = recursive(str, patern, rc, init_mx(0, 0));
	return (ret);
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

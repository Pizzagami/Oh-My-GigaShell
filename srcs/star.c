/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   star.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braimbau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 10:30:03 by braimbau          #+#    #+#             */
/*   Updated: 2020/12/03 10:53:35 by braimbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "token.h"
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>

int			ft_strcmp1(char *s1, char *s2)
{
	unsigned int i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - s2[i]);
		i++;
	}
	if ((s1[i] && !s2[i]) || (!s1[i] && s2[i]))
		return ((unsigned char)s1[i] - s2[i]);
	return (0);
}

int			ft_strcmp2(char *s1, char *s2)
{
	unsigned int i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - s2[i]);
		i++;
	}
	if (!s1[i] && s2[i] == '.')
		return (1);
	if (!s2[i] && s1[i] == '.')
		return (-1);
	if ((s1[i] && !s2[i]) || (!s1[i] && s2[i]))
		return ((unsigned char)s1[i] - s2[i]);
	return (0);
}

void		print_list(t_listdir *a)
{
	while (a)
	{
		printf("%s\n", a->name);
		a = a->next;
	}
}

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

char		*ft_strjoin_sep(char *s1, char *s2, char c)
{
	int		i;
	int		x;
	char	*dest;

	i = ft_strlen(s1) + ft_strlen(s2);
	dest = malloc(sizeof(char) * (i + 2));
	if (!dest)
		return (NULL);
	x = 0;
	while (s1 && s1[x])
	{
		dest[x] = s1[x];
		x++;
	}
	dest[x] = c;
	x++;
	i = 0;
	while (s2 && s2[i])
	{
		dest[x] = s2[i];
		x++;
		i++;
	}
	dest[x] = 0;
	return (dest);
}

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

char		*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	char			*ptr;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i])
		i++;
	if (!(ptr = malloc((len + 1) * sizeof(char))))
		return (NULL);
	if (i <= start)
	{
		ptr[0] = 0;
		return (ptr);
	}
	i = 0;
	while (i < len && s[start + i])
	{
		ptr[i] = s[start + i];
		i++;
	}
	ptr[i] = 0;
	return (ptr);
}

int			srcchar(char c, char *str)
{
	int x;

	x = 0;
	while (str[x])
	{
		if (str[x] == c)
			return (x);
		x++;
	}
	return (-1);
}

void		removechar(char **str, int x)
{
	while ((*str)[x + 1])
	{
		(*str)[x] = (*str)[x + 1];
		x++;
	}
	(*str)[x] = 0;
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

int			recursive(char *str, char *patern, int rc, int xp, int xs)
{
	int i;

	if (xs == 0 && xp == 0 && str[xs] == '.' && str[xs] != patern[xp])
		return (0);
	if (!str[xs] && (!patern[xp] || rc == 0))
		return (1);
	else if (!str[xs])
		return (0);
	if (patern[xp] != CSTAR)
	{
		if (str[xs] == patern[xp])
			return (recursive(str, patern, rc, xp + 1, xs + 1));
		else
			return (0);
	}
	i = rc;
	while (i > -1)
	{
		if (recursive(str, patern, rc - i, xp + 1, xs + i))
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
	ret = recursive(str, patern, rc, 0, 0);
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

int			megastar(char *patern, char *path, char *minipath, char **final)
{
	DIR				*dir;
	struct dirent	*dirent;
	t_listdir		*list;
	t_listdir		*actual;
	int				sfdo;

	sfdo = 0;
	if (srcchar('/', patern) != -1)
	{
		sfdo = 1;
		patern[ft_strlen(patern) - 1] = 0;
	}
	actual = NULL;
	dir = opendir(path);
	if (dir == NULL)
		return (1);
	while ((dirent = readdir(dir)) != NULL)
	{
		if (superstar(dirent->d_name, patern) && (!sfdo || is_dir(path, dirent->d_name)))
		{
			list = malloc(sizeof(t_list));
			if (sfdo)
				list->name = ft_strjoin_sep(dirent->d_name, NULL, '/');
			else
				list->name = ft_strdup(dirent->d_name);
			list->next = actual;
			actual = list;
		}
	}
	sort_list(actual);
	add_list(actual, minipath, final);
	free_list(actual);
	closedir(dir);
	return (0);
}

void		throughdir(char *multipath, char *patern, t_listdir *a, char **final)
{
	char *path;
	char *minipath;
	char *newminipath;
	char *newpatern;
	char *newpath;

	minipath = multipath;
	path = multipath + ft_strlen(multipath) + 1;
	while (a)
	{
		newpatern = ft_substr(patern, srcchar('/', patern) + 1,
		ft_strlen(patern) - srcchar('/', patern) + 1);
		newpath = ft_strjoin_sep(path, a->name, '/');
		if (minipath[0])
		{
			newminipath = ft_strjoin_sep(minipath, a->name, '/');
			recurdir(newpatern, newpath, newminipath, final);
			free(newminipath);
		}
		else
		{
			recurdir(newpatern, newpath, a->name, final);
		}
		free(newpatern);
		free(newpath);
		a = a->next;
	}
	free(multipath);
}

int			recurdir(char *patern, char *path, char *minipath, char **final)
{
	DIR				*dir;
	struct dirent	*dirent;
	char			*dirname;
	t_listdir		*actual;

	actual = NULL;
	if (srcchar('/', patern) == -1 || srcchar('/', patern) == (int)ft_strlen(patern) - 1)
	{
		if (patern[0] != '/')
			return (megastar(patern, path, minipath, final));
		else
			return (megastar("\x01", "/", minipath, final));
	}
	dir = opendir(path);
	if (dir == NULL)
		return (1);
	dirname = ft_substr(patern, 0, srcchar('/', patern));
	while ((dirent = readdir(dir)) != NULL)
	{
		if (is_dir(path, dirent->d_name) && superstar(dirent->d_name, dirname))
		{
			actual = new_maillon(actual, ft_strdup(dirent->d_name));
		}
	}
	sort_list_dsm(actual);
	throughdir(ft_strjoin_sep(minipath, path, '\0'), patern, actual, final);
	free_list(actual);
	free(dirname);
	closedir(dir);
	return (0);
}

void		dereplace_stars(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == CSTAR)
			str[i] = '*';
		i++;
	}
}

int			gigastar(char *patern, char **final, char *home)
{
	char *path;
	char *minipath;

	*final = NULL;
	if (patern[0] == '/')
	{
		minipath = "";
		path = "/";
		recurdir(patern + 1, path, minipath, final);
	}
	else if (patern[0] == '~')
	{
		path = home;
		minipath = home;
		recurdir(patern + 2, path, minipath, final);
	}
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

t_token		*starize_list(t_token *first, t_token *max, char *home)
{
	t_token	*tmp;
	t_token	*tmp2;
	char	*str;
	t_token	*a;

	a = first;
	while (a && a != max)
	{
		if (a == first && srcchar(CSTAR, a->str) != -1)
		{
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
		}
		if (a->next && a->next != max && srcchar(CSTAR, a->next->str) != -1)
		{
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
		}
		if (a && a != max)
			a = a->next;
	}
	return (first);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braimbau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 17:26:36 by braimbau          #+#    #+#             */
/*   Updated: 2020/11/26 21:22:47 by braimbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"

void	free_d_tab(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int		is_in_directory(char *dirname, char *file)
{
	DIR				*dir;
	struct dirent	*dirent;

	dir = opendir(dirname);
	while ((dirent = readdir(dir)))
	{
		if (ft_strcmp(dirent->d_name, file) == 0)
		{
			closedir(dir);
			return (1);
		}
	}
	closedir(dir);
	return (0);
}

char *get_implicit_path(t_env *env, char *str)
{
	char	**tab;
	int		i;
	char	*path;
	char	*tmp;
	char	*test;

	i = 0;
	test = get_env(env, "PATH");
	tab = ft_split(test, ':');
	while (tab[i])
	{
		if (is_in_directory(tab[i], str))
		{
			path = ft_strjoin(tab[i], "/");
			tmp = path;
			path = ft_strjoin(path, str);
			free(tmp);
			free_d_tab(tab);
			return (path);
		}
		i++;
	}
	free_d_tab(tab);
	return (NULL);
}

char *get_path(t_env *env, char *str)
{
	char path[4096];
	char *home;
	char *tmp;

	if (str[0] == '.')
	{
		getcwd(path, 4096);
		str = ft_substr(str, 1, ft_strlen(str) -1);
		tmp = str;
		str = ft_strjoin(path, str);
		free(tmp);
	}
	else if (str[0] == '~')
	{
		home = get_env(env, "HOME");
		str = ft_substr(str, 1, ft_strlen(str) -1);
		tmp = str;
		str = ft_strjoin(home, str);
		free(tmp);
		free(home);
	}
	else
		str = get_implicit_path(env, str);
	return (str);
}

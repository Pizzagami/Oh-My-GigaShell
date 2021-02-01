/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braimbau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 17:26:36 by braimbau          #+#    #+#             */
/*   Updated: 2021/02/01 10:03:50 by braimbau         ###   ########.fr       */
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
	char			*d_name_up;
	char			*file_up;
	int				ret;

	ret = 0;
	dir = opendir(dirname);
	file_up = ft_strdup(file);
	str_low(file_up);
	while ((dirent = readdir(dir)))
	{
		d_name_up = ft_strdup(dirent->d_name);
		str_low(d_name_up);
		if (ft_strcmp(d_name_up, file_up) == 0)
		{
			ret = 1;
			break ;
		}
		free(d_name_up);
	}
	free(file_up);
	closedir(dir);
	return (ret);
}

char	*get_implicit_path(t_env *env, char *str, int i)
{
	char	**tab;
	char	*path;
	char	*tmp;
	char	*test;

	test = get_env(env, "PATH");
	if (test == NULL)
		return (NULL);
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

char	*get_path(t_env *env, char *str)
{
	char path[4096];
	char *home;
	char *tmp;

	if (str[0] == '/')
		return (str);
	if (str[0] == '.')
	{
		getcwd(path, 4096);
		str = ft_substr(str, 1, ft_strlen(str) - 1);
		tmp = str;
		str = ft_strjoin(path, str);
		free(tmp);
	}
	else if (str[0] == '~')
	{
		home = get_env(env, "HOME");
		str = ft_substr(str, 1, ft_strlen(str) - 1);
		tmp = str;
		str = ft_strjoin(home, str);
		mfree(tmp, home);
	}
	else
		str = get_implicit_path(env, str, 0);
	return (str);
}

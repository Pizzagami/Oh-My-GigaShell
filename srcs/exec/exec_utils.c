/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pizzagami <pizzagami@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 11:11:48 by braimbau          #+#    #+#             */
/*   Updated: 2021/02/15 08:47:48 by braimbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int		env_size(t_env *first)
{
	int		compteur;
	t_env	*tmp;

	tmp = first;
	compteur = 0;
	while (tmp)
	{
		compteur++;
		tmp = tmp->next;
	}
	return (compteur);
}

char	**link_tab(t_env *env)
{
	char	**str;
	char	*tmp;
	int		x;
	int		j;

	j = 0;
	x = env_size(env);
	str = (char**)malloc(sizeof(char*) * (x + 1));
	str[x] = NULL;
	while (j < x)
	{
		tmp = ft_strjoin(env->name, "=");
		str[j] = ft_strjoin(tmp, env->val);
		free(tmp);
		env = env->next;
		j++;
	}
	str[j] = NULL;
	return (str);
}

void	exec_binary_son(t_omm omm, char **tab, char **tabenv)
{
	char	*path;
	int		ret;

	path = get_path(omm.env, tab[0]);
	if (!path)
	{
		ft_putstr_fd("bashy: ", 2);
		ft_putstr_fd(tab[0], 2);
		ft_putstr_fd(" : command not found\n", 2);
		free(tab);
		exit(127);
	}
	ret = is_exec(path);
	if (ret != 1)
	{
		free(tab);
		ft_putstr_fd("bashy: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd((!ret) ? ": Permision denied\n" :
				" No such file or directory\n", 2);
		exit((ret) ? 127 : 126);
	}
	tabenv = link_tab(omm.env);
	execve(path, tab, tabenv);
}

void	son_pipeline(int pfd[2], t_omm *omm, t_pipeline *pipeline)
{
	close(pfd[0]);
	dup2(pfd[1], 1);
	close(pfd[1]);
	omm->stdout = dup(pfd[1]);
	if (pipeline->command)
		exec_command(pipeline->command, *omm);
	exit(0);
}

void	free_tab(char **tab)
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

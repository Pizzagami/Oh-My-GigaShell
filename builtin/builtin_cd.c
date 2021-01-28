/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selgrabl <selgrabl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 10:23:00 by selgrabl          #+#    #+#             */
/*   Updated: 2021/01/28 10:00:01 by selgrabl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

void	builtin_cd(char *path, t_env *env)
{
	char	htap[PATH_MAX];
	char	**oldpwd;
	char	**pwd;

	if (!path || !ft_strcmp(path, "~"))
		path = *get_env2(env, "HOME");
	if (chdir(path) == 0)
	{
		pwd = get_env2(env, "PWD");
		oldpwd = get_env2(env, "OLDPWD");
		if (!oldpwd && !pwd)
		{
			free(oldpwd);
			oldpwd = pwd;
			*pwd = getcwd(htap, PATH_MAX - 1);
		}
	}
	else
	{
		ft_putstr("bash: cd: ");
		perror(path);
	}
}

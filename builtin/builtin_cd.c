/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selgrabl <selgrabl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 10:23:00 by selgrabl          #+#    #+#             */
/*   Updated: 2021/02/10 13:54:56 by braimbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

void	norme_cd(char **oldpwd, char **pwd, char htap[PATH_MAX], char *path)
{
	char *pwdtmp;

	if (*oldpwd != 0 && *pwd != 0)
	{
		if (path[0] == '-' && path[1] == 0)
		{
			pwdtmp = *pwd;
			*pwd = *oldpwd;
			*oldpwd = pwdtmp;
			chdir(*pwd);
			builtin_pwd();
		}
		else
		{
			free(*oldpwd);
			*oldpwd = *pwd;
			*pwd = ft_strdup(getcwd(htap, PATH_MAX - 1));
		}
	}
}

void	builtin_cd(char *path, t_env *env)
{
	char	htap[PATH_MAX];
	char	**oldpwd;
	char	**pwd;

	if (!path || !ft_strcmp(path, "~"))
		path = *get_env2(env, "HOME");
	if (chdir(path) == 0 || (path[0] == '-' && path[1] == 0))
	{
		pwd = get_env2(env, "PWD");
		oldpwd = get_env2(env, "OLDPWD");
		norme_cd(oldpwd, pwd, htap, path);
	}
	else
	{
		ft_putstr_fd("bash: cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
	}
}

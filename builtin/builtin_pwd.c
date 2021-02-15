/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selgrabl <selgrabl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 10:23:00 by selgrabl          #+#    #+#             */
/*   Updated: 2021/02/15 15:51:32 by braimbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "limits.h"

void	builtin_pwd(t_env *env)
{
	char path[PATH_MAX];

	if (getcwd(path, PATH_MAX - 1))
		ft_putstr(getcwd(path, PATH_MAX - 1));
	else
		ft_putstr(get_env(env, "PWD"));
	ft_putstr("\n");
	return ;
}

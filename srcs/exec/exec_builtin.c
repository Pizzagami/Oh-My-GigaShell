/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braimbau <braimbau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 15:24:37 by raimbault         #+#    #+#             */
/*   Updated: 2021/02/15 14:25:07 by braimbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "errno.h"
#include "stdio.h"
#include "fcntl.h"

int		is_builtin(char *exec)
{
	if (ft_strcmp(exec, "echo") == 0)
		return (1);
	if (ft_strcmp(exec, "cd") == 0)
		return (2);
	if (ft_strcmp(exec, "pwd") == 0)
		return (3);
	if (ft_strcmp(exec, "env") == 0)
		return (4);
	if (ft_strcmp(exec, "export") == 0)
		return (5);
	if (ft_strcmp(exec, "unset") == 0)
		return (6);
	if (ft_strcmp(exec, "exit") == 0)
		return (7);
	return (0);
}

int		exec_builtin(char *exec, char **tab, t_env *env)
{
	int i;
	int x;

	x = 0;
	i = 0;
	i = is_builtin(exec);
	if (i > 0)
		tab++;
	if (i == 2)
		x = builtin_cd(*tab, env);
	if (i == 3)
		builtin_pwd(env);
	if (i == 4)
		builtin_env(env);
	if (i == 5)
		builtin_export(tab, &env);
	if (i == 6)
		builtin_unset(tab, &env);
	if (i == 7)
	{
		builtin_exit(env, tab);
		x = 1;
	}
	if (i == 1 && *tab)
		buitin_echo(tab);
	return (x);
}

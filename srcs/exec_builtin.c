/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selgrabl <selgrabl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 15:24:37 by raimbault         #+#    #+#             */
/*   Updated: 2021/01/21 17:02:57 by selgrabl         ###   ########.fr       */
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
	int i; //verif taille tab

	i = 0;
	i = is_builtin(exec);
	if (i > 0)
		tab++;
	if (i == 1 && *tab)
		buitin_echo(tab);
	else if (i == 1)
		return(0);
	if (i == 2)
		builtin_cd(*tab, env);
	if (i == 3)
		builtin_pwd();
	if (i == 4)
		builtin_env(env);
	if (i == 5)
		builtin_export(tab, &env); //message d erreur si probleme
	if (i == 6)
		builtin_unset(tab, &env);
	if (i == 7)
		builtin_exit(env);
	return (0);
}

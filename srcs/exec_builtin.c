/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pizzagami <pizzagami@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 15:24:37 by raimbault         #+#    #+#             */
/*   Updated: 2020/12/02 15:47:05 by pizzagami        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "errno.h"
#include "stdio.h"
#include "fcntl.h"

int		is_builtin(char *executable)
{
	if (ft_strcmp(executable, "echo") == 0)
		return (1);
	if (ft_strcmp(executable, "cd") == 0)
		return (2);
	return (0);
}

int		exec_builtin(char *executable, char **tab, char **env)
{
	int i;

	(void)env;
	i = is_builtin(executable);
	(void)tab;
	if (i == 1)
		buitin_echo(tab);
	if (i == 2)
		builtin_cd(tab);
	return (0);
}

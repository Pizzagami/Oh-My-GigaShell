/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raimbaultbrieuc <marvin@42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 15:24:37 by raimbault         #+#    #+#             */
/*   Updated: 2020/12/02 13:30:44 by braimbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "errno.h"
#include "stdio.h"
#include "fcntl.h"

void	buitin_echo(char **str)
{
	int n;

	n = 0;
	str++;
	if (ft_strcmp("-n", *str) == 0)
	{
		n = 1;
		str++;
	}
	while (*str)
	{
		ft_putstr(*str);
		str++;
	}
	if (n == 0)
	{
		write(1, "\n", 1);
	}
}

void	builtin_cd(char **tab)
{
	int		fd;
	char	*path;

	path = tab[1];
	fd = open(path, O_RDONLY);
	if (!path)
		return ;
	if (chdir(path) == -1)
	{
		perror("chdir()");
	}
	/*if (fd < 0) // verifier les differente erreurs (et perror?)
	{
		ft_putstr("cd: no such file or directory: ");
		ft_putstr(path);
	}
	else
	{
		chdir(path);
	}*/
	close(fd);
}

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
	if (i == 1)
		buitin_echo(tab);
	if (i == 2)
		builtin_cd(tab);
	return (0);
}

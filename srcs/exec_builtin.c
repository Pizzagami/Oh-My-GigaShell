/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raimbaultbrieuc <marvin@42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 15:24:37 by raimbault         #+#    #+#             */
/*   Updated: 2020/10/28 14:44:01 by braimbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int strcmpnocase(char *s1, char *s2)
{
	int i;

	i = 0;
	if (ft_strlen(s1) != ft_strlen(s2))
		return (ft_strlen(s1) - ft_strlen(s2));
	while (s1[i])
	{
		if (s1[i] >= 'A' && s1[i] <= 'Z')
		{
			if (s1[i] != s2[i] && s1[i] + 32 != s2[i])
				return (i);
		}
		else if (s1[i] >= 'a' && s1[i] <= 'a')
		{
			if (s1[i] != s2[i] && s1[i] - 32 != s2[i])
				return (i);
		}
		else if (s1[i] != s2[i])
			return (i);
		i++;
	}
	return (0);
}

int	is_builtin(char *executable)
{
	if (strcmpnocase(executable, "test1"))
		return (1);
	if (strcmpnocase(executable, "test2"))
		return (2);
	return (0);
}

int exec_builtin(char *executable, char **tab, char **env)
{
	(void)executable;
	(void)tab;
	(void)env;
	printf("Boooooonnnnjour !\n");
	return (42);
}

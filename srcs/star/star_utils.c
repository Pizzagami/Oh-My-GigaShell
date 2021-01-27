/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   star_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braimbau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 15:27:50 by braimbau          #+#    #+#             */
/*   Updated: 2021/01/08 15:27:52 by braimbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		mfree(char *s1, char *s2)
{
	if (s1)
		free(s1);
	if (s2)
		free(s2);
}

int			ft_strcmp1(char *s1, char *s2)
{
	unsigned int i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - s2[i]);
		i++;
	}
	if ((s1[i] && !s2[i]) || (!s1[i] && s2[i]))
		return ((unsigned char)s1[i] - s2[i]);
	return (0);
}

int			ft_strcmp2(char *s1, char *s2)
{
	unsigned int i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - s2[i]);
		i++;
	}
	if (!s1[i] && s2[i] == '.')
		return (1);
	if (!s2[i] && s1[i] == '.')
		return (-1);
	if ((s1[i] && !s2[i]) || (!s1[i] && s2[i]))
		return ((unsigned char)s1[i] - s2[i]);
	return (0);
}

void		print_list(t_listdir *a)
{
	while (a)
	{
		printf("%s\n", a->name);
		a = a->next;
	}
}

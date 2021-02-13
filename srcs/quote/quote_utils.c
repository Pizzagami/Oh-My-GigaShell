/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braimbau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 10:49:19 by braimbau          #+#    #+#             */
/*   Updated: 2021/02/13 13:29:27 by braimbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	delete_unquoted_newlines(char *str, char *quot)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (quot[i] == '0' && str[i] == '\n')
		{
			remove_char(str, i);
			remove_char(quot, i);
		}
		else
			i++;
	}
}

int		esc_bksl(int *x, int *i, char *str, char *quot)
{
	if (str[*i] == 92)
	{
		remove_char(str, *i);
		if (!str[*i])
		{
			free(quot);
			return (1);
		}
		quot[*x] = '3';
	}
	return (0);
}

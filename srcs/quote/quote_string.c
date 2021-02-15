/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braimbau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 16:17:48 by braimbau          #+#    #+#             */
/*   Updated: 2021/02/15 10:44:45 by braimbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "libft.h"
#include "token.h"
#include "minishell.h"

int		dquote(int *x, int *i, char *str, char *quot)
{
	remove_char(str, *i);
	if (str[*i] && str[*i] != 34)
	{
		esc_bksl(x, i, str, quot);
		quot[*x] = 'b';
		(*x)++;
		(*i)++;
	}
	while (str[*i] && (str[*i] != 34 || quot[*i] == '3'))
	{
		esc_bksl(x, i, str, quot);
		quot[*x] = '2';
		(*x)++;
		(*i)++;
	}
	if (!str[*i])
	{
		free(quot);
		return (1);
	}
	remove_char(str, *i);
	return (0);
}

int		squote(int *x, int *i, char *str, char *quot)
{
	remove_char(str, *i);
	if (str[*i] && str[*i] != 39)
	{
		quot[*x] = 'a';
		(*x)++;
		(*i)++;
	}
	while (str[*i] && (str[*i] != 39 || quot[*i] == '3'))
	{
		quot[*x] = '1';
		(*x)++;
		(*i)++;
	}
	if (!str[*i])
	{
		free(quot);
		return (1);
	}
	remove_char(str, *i);
	return (0);
}

int		backslash(int *x, int *i, char *str, char *quot)
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
		(*x)++;
		(*i)++;
	}
	else
	{
		quot[*x] = '0';
		(*x)++;
		(*i)++;
	}
	return (0);
}

int		switch_quot(int *x, int *i, char *str, char *quot)
{
	if (str[*i] == 34 && dquote(i, x, str, quot))
		return (1);
	if (str[*i] == 39 && squote(i, x, str, quot))
		return (2);
	if (backslash(i, x, str, quot))
		return (3);
	return (0);
}

char	*quote_string(char **pstr, int *ec)
{
	int		i;
	int		x;
	char	*quot;
	char	*str;

	str = *pstr;
	i = 0;
	x = 0;
	quot = malloc(sizeof(char) * (strlen(str) + 1));
	while (str[i])
	{
		if ((*ec = switch_quot(&x, &i, str, quot)))
			return (NULL);
	}
	quot[x] = 0;
	replace_chars(pstr, &quot);
	delete_unquoted_newlines(*pstr, quot);
	return (quot);
}

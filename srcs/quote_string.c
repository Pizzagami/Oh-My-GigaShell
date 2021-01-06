/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braimbau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 14:24:24 by braimbau          #+#    #+#             */
/*   Updated: 2020/12/17 16:26:40 by braimbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "libft.h"
#include "minishell.h"
#include "token.h"

void	remove_char(char *str, int index)
{
	int x;

	x = 0;
	while (x < index)
		x++;
	while (str[x])
	{
		str[x] = str[x + 1];
		x++;
	}
}

void	add_char(char **str, int index, char c)
{
	char	*ret;
	int		i;
	char	*tmp;

	if (index > (int)ft_strlen(*str) || index < 0)
		return ;
	i = 0;
	ret = malloc((ft_strlen(*str) + 2) * sizeof(char));
	while (i < index)
	{
		ret[i] = (*str)[i];
		i++;
	}
	ret[i] = c;
	i++;
	while ((*str)[i - 1])
	{
		ret[i] = (*str)[i - 1];
		i++;
	}
	ret[i] = 0;
	tmp = *str;
	*str = ret;
	free(tmp);
}

int		is_name(char *str, char *quot, int i)
{
	if (str[i] && str[i] != ' ' && str[i] != '\\' && str[i] != '/'
		&& str[i] != '\n' && str[i - 1] != '?' && str[i] != '$'
		&& quot[i] != 'a' && quot[i] != 'b' && quot[i] != '1'
		&& quot[i] != '3')
		return (1);
	return (0);
}

void	replace_chars(char **pstr, char **pquot)
{
	int		i;
	char	*str;
	char	*quot;

	str = *pstr;
	quot = *pquot;
	i = 0;
	while (str && str[i])
	{
		if (str[i] == '*' && quot[i] == '0')
			str[i] = CSTAR;
		if (str[i] == '$' && quot[i] != '1' && quot[i] != 'a')
		{
			str[i] = CDOLLAR;
			i++;
			while (is_name(str, quot, i))
				i++;
			add_char(pstr, i, CDOLLEND);
			add_char(pquot, i, (*pquot)[i]);
			str = *pstr;
			quot = *pquot;
		}
		i++;
	}
}

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
		i++;
	}
}

int		dquote_string(int *x, int *i, char *str, char *quot)
{
	if (str[*i] == DQUOT)
	{
		remove_char(str, *i);
		if (str[*i] && str[*i] != DQUOT)
		{
			quot[*x] = 'b';
			(*x)++;
			(*i)++;
		}
		while (str[*i] && str[*i] != DQUOT)
		{
			quot[*x] = '2';
			(*x)++;
			(*i)++;
		}
		if (!str[*i])
		{
			free(quot);
			*x = 1;
			return (1);
		}
		remove_char(str, *i);
	}
	return (0);
}

int		squot_string(int *x, int *i, char *str, char *quot)
{
	if (str[*i] == SQUOT)
	{
		remove_char(str, *i);
		if (str[*i] && str[*i] != SQUOT)
		{
			quot[*x] = 'a';
			(*x)++;
			(*i)++;
		}
		while (str[*i] && str[*i] != SQUOT)
		{
			quot[*x] = '1';
			(*x)++;
			(*i)++;
		}
		if (!str[*i])
		{
			free(quot);
			*x = 2;
			return (2);
		}
		remove_char(str, *i);
	}
	return (0);
}

int		back_string(int *x, int *i, char *str, char *quot)
{
	if (str[*i] == BACKSLASH)
	{
		remove_char(str, *i);
		if (!str[*i])
		{
			free(quot);
			return (3);
			*x = 3;
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

char	*quote_string(char **pstr, int *ec)
{
	int		i;
	int		x;
	char	*quot;

	i = 0;
	x = 0;
	if ((quot = malloc(sizeof(char) * (strlen(*pstr) + 1))) == NULL)
	{
		*ec = 18;
		return (NULL);
	}
	while ((*pstr)[i])
	{
		if (dquote_string(&x, &i, *pstr, quot)
			|| squot_string(&x, &i, *pstr, quot)
			|| back_string(&x, &i, *pstr, quot))
		{
			*ec = x;
			return (NULL);
		}
	}
	quot[x] = 0;
	replace_chars(pstr, &quot);
	delete_unquoted_newlines(*pstr, quot);
	return (quot);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_string.c								        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   by: raimbaultbrieuc <marvin@42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   created: 2020/07/15 16:13:31 by raimbault         #+#    #+#             */
/*   updated: 2020/11/29 20:00:43 by braimbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "libft.h"
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
	{
		*str = NULL;
		return ;
	}
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
			while (str[i] && str[i] != ' ' && str[i] != '\\' && str[i] != '/' && str[i - 1] != '?' && str[i] != '$' && quot[i] != 'a' && quot[i] != 'b' && quot[i] != '1' && quot[i] != '3')
				i++;
			add_char(pstr, i, CDOLLEND);
			add_char(pquot, i, (*pquot)[i]);
			str = *pstr;
			quot = *pquot;
		}
		i++;
	}
}

void delete_unquoted_newlines(char *str, char *quot)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (quot[i] == '0' && str[i] == '\n')
			remove_char(str, i);
		i++;
	}
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
		if (str[i] == 34)
		{
			remove_char(str, i);
			if (str[i] && str[i] != 34)
			{
				quot[x] = 'b';
				x++;
				i++;
			}
			while (str[i] && str[i] != 34)
			{
				quot[x] = '2';
				x++;
				i++;
			}
			if (!str[i])
			{
				*ec = 1;
				free(quot);
				return (NULL);
			}
			remove_char(str, i);
		}
		if (str[i] == 39)
		{
			remove_char(str, i);
			if (str[i] && str[i] != 39)
			{
				quot[x] = 'a';
				x++;
				i++;
			}
			while (str[i] && str[i] != 39)
			{
				quot[x] = '1';
				x++;
				i++;
			}
			if (!str[i])
			{
				*ec = 2;
				free(quot);
				return (NULL);
			}
			remove_char(str, i);
		}
		if (str[i] == 92)
		{
			remove_char(str, i);
			if (!str[i])
			{
				*ec = 3;
				free(quot);
				return (NULL);
			}
			quot[x] = '3';
			x++;
			i++;
		}
		else
		{
			quot[x] = '0';
			x++;
			i++;
		}
	}
	quot[x] = 0;
	replace_chars(pstr, &quot);
	delete_unquoted_newlines(str, quot);
	return (quot);
}

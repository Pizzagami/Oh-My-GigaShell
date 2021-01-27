/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_char_edit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braimbau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 10:33:38 by braimbau          #+#    #+#             */
/*   Updated: 2021/01/15 11:04:40 by braimbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int		condition(int i, char *str, char *quot)
{
	if (str[i] && str[i] != ' ' && str[i] != '\\' && str[i] != '/'
		&& str[i - 1] != '?' && str[i] != '$' && quot[i] != 'a'
		&& quot[i] != 'b' && quot[i] != '1' && quot[i] != '3'
		&& (1 || quot[i - 1] == 'b' || quot[i - 1] == 'a'
		|| quot[i] == quot[i - 1]))
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
			while (condition(i, str, quot))
				i++;
			add_char(pstr, i, CDOLLEND);
			add_char(pquot, i, (*pquot)[i]);
			str = *pstr;
			quot = *pquot;
		}
		i++;
	}
}

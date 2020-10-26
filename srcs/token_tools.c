/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raimbaultbrieuc <marvin@42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 14:57:27 by raimbault         #+#    #+#             */
/*   Updated: 2020/10/23 14:17:23 by braimbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "token.h"


int		ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1 && s2 && s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	if (!s1[i] && !s2[i])
		return (1);
	return (0);
}

char	*lower_case(char *str)
{
	int i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] >= 'A' && str[i] <= 'Z')
			str[i] += 32;
		i++;
	}
	return (str);
}

t_token *create_simple_token_list(char *str)
{
	t_token	*token_start;
	t_token *token_current;
	int		i;
	int		x;

	token_start = NULL;
	token_current = NULL;
	i = 0;
	while (str[i])
	{
		i += (str[i] == ' ') ? 1 : 0;
		x = 0;
		while (str[i + x] && str[i + x] != ' ')
			x++;
		add_token(&token_current, VOID, create_str(str, i, x));
		if (token_start == NULL)
			token_start = token_current;
		i += x;
		i += (str[i] == ' ') ? 1 : 0;
	}
	return (token_start);
}

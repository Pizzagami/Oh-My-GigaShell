/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_creation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raimbaultbrieuc <marvin@42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 15:30:31 by raimbault         #+#    #+#             */
/*   Updated: 2021/01/31 14:28:49 by braimbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "parser.h"

int		set_double_token(char c, char c2, t_token **token_current)
{
	if (c == '|' && c2 == '|')
	{
		add_token_malloc(token_current, OR_IF, "||", 2);
		return (1);
	}
	if (c == '&' && c2 == '&')
	{
		add_token_malloc(token_current, AND_IF, "&&", 2);
		return (1);
	}
	if (c == '>' && c2 == '>')
	{
		add_token_malloc(token_current, DGREAT, ">>", 2);
		return (1);
	}
	if (c == '<' && c2 == '<')
	{
		add_token_malloc(token_current, DLESS, "<<", 2);
		return (1);
	}
	return (0);
}

int		special_tokens_switch(int i, char *str, t_token **token)
{
	if (set_double_token(str[i], str[i + 1], token))
		i++;
	else
		set_special_token(str[i], token);
	i++;
	return (i);
}

t_mx	init_mx2(char *str, char *quot)
{
	t_mx mx;

	mx.str = str;
	mx.quot = quot;
	return (mx);
}

int		create_classic_token(int i, t_mx b, t_token **token_start,
		t_token **token_current)
{
	int x;

	x = 0;
	while ((b.str[i + x] && b.str[i + x] != ' '
			&& !is_special_char(b.str[i + x])) || b.quot[i + x] > '0')
		x++;
	add_token(token_current, VOID, create_str(b.str, i, x));
	if (*token_start == NULL)
		*token_start = *token_current;
	return (x);
}

t_token	*create_token_list(char *str, char *quot)
{
	t_token	*token_start;
	t_token *token_current;
	int		i;

	token_current = NULL;
	token_start = NULL;
	i = 0;
	while (str[i])
	{
		if (str[i] == ' ' && quot[i] == '0')
			i++;
		else if (is_special_char(str[i]) &&
				quot[i] == '0')
		{
			i = special_tokens_switch(i, str, &token_current);
			if (token_start == NULL)
				token_start = token_current;
		}
		else
			i += create_classic_token(i, init_mx2(str, quot), &token_start,
				&token_current);
		i += (str[i] == ' ' && quot[i] == '0') ? 1 : 0;
	}
	return (token_start);
}

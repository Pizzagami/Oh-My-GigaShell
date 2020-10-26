/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_creation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raimbaultbrieuc <marvin@42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 15:30:31 by raimbault         #+#    #+#             */
/*   Updated: 2020/10/23 13:55:41 by braimbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "parser.h"

void	set_special_token(char c, t_token **token_current)
{
	if (c == '(')
		add_token_malloc(token_current, OBRA, "(", 1);
	if (c == ')')
		add_token_malloc(token_current, CBRA, ")", 1);
	if (c == '\n')
		add_token_malloc(token_current, NEWLINE, "\n", 1);
	if (c == ';')
		add_token_malloc(token_current, SEMI, ";", 1);
	if (c == '>')
		add_token_malloc(token_current, GREAT, ">", 1);
	if (c == '<')
		add_token_malloc(token_current, LESS, "<", 1);
	if (c == '&')
		add_token_malloc(token_current, AND, "&", 1);
	if (c == '|')
		add_token_malloc(token_current, PIPE, "|", 1);
}

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

int		create_dquote_token(char *str, int i, t_token **token, int *ec)
{
	int x;

	x = 0;
	i++;
	while (str[i + x] && str[i + x] != '"')
		x++;
	if (str[i + x] == 0)
	{
		*ec = 10;
		return (x + 1);
	}
	else
		add_token(token, WORD, create_str(str, i, x));
	return (x + 1);
}

int		special_tokens_switch(int i, char *str, t_token **token, int *ec)
{
	if (str[i] == '"')
		i += create_dquote_token(str, i, token, ec);
	if (set_double_token(str[i], str[i + 1], token))
		i++;
	else
		set_special_token(str[i], token);
	i++;
	return (i);
}

t_token	*create_token_list(char *str, int *ec)
{
	t_token	*token_start;
	t_token *token_current;
	int		i;
	int		x;

	token_current = NULL;
	token_start = NULL;
	i = 0;
	while (str[i])
	{
		i += (str[i] == ' ') ? 1 : 0;
		if (is_special_char(str[i]))
		{
			i = special_tokens_switch(i, str, &token_current, ec);
		}
		else
		{
			x = 0;
			while (str[i + x] && str[i + x] != ' ' &&
					!is_special_char(str[i + x]))
				x++;
			add_token(&token_current, VOID, create_str(str, i, x));
			if (token_start == NULL)
				token_start = token_current;
			i += x;
		}
		i += (str[i] == ' ') ? 1 : 0; //si ca merde cest a cause de ca
	}
	return (token_start);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_creation_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raimbaultbrieuc <marvin@42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 15:33:29 by raimbault         #+#    #+#             */
/*   Updated: 2021/01/08 11:01:33 by braimbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	add_token(t_token **token_current, t_type type, char *str)
{
	t_token *tmp;

	tmp = malloc(sizeof(t_token));
	tmp->type = type;
	tmp->str = str;
	tmp->next = NULL;
	if (type == VOID)
		tmp->type = WORD;
	if (*token_current)
	{
		(*token_current)->next = tmp;
		(*token_current) = (*token_current)->next;
	}
	else
		(*token_current) = tmp;
}

void	add_token_malloc(t_token **token_current, t_type type, char *str, int s)
{
	t_token *tmp;

	tmp = malloc(sizeof(t_token));
	tmp->type = type;
	tmp->str = malloc(sizeof(char) * (s + 1));
	tmp->str[0] = str[0];
	tmp->str[1] = 0;
	if (s == 2)
	{
		tmp->str[1] = str[1];
		tmp->str[2] = 0;
	}
	tmp->next = NULL;
	if (type == VOID)
		tmp->type = WORD;
	if (*token_current)
	{
		(*token_current)->next = tmp;
		(*token_current) = (*token_current)->next;
	}
	else
		(*token_current) = tmp;
}

char	*create_str(char *str, int start, int len)
{
	char	*ret;
	int		i;

	ret = malloc(sizeof(char) * (len + 1));
	i = 0;
	while (i < len)
	{
		ret[i] = str[start + i];
		i++;
	}
	ret[i] = 0;
	return (ret);
}

int		is_special_char(char c)
{
	char	*special;
	int		i;

	special = "()<>|&;";
	i = 0;
	while (special[i])
	{
		if (c == special[i])
			return (1);
		i++;
	}
	return (0);
}

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

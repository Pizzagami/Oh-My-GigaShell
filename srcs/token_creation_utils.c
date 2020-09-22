/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_creation_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raimbaultbrieuc <marvin@42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 15:33:29 by raimbault         #+#    #+#             */
/*   Updated: 2020/07/15 16:28:59 by raimbaul         ###   ########.fr       */
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
	(*token_current)->next = tmp;
	if (type == VOID)
		tmp->type = WORD;
	(*token_current) = (*token_current)->next;
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
	(*token_current)->next = tmp;
	if (type == VOID)
		tmp->type = WORD;
	(*token_current) = (*token_current)->next;
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

	special = "()<>|&*';\"";
	i = 0;
	while (special[i])
	{
		if (c == special[i])
			return (1);
		i++;
	}
	return (0);
}

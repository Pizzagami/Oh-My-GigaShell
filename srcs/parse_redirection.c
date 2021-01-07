/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raimbaultbrieuc <marvin@42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 16:34:28 by raimbault         #+#    #+#             */
/*   Updated: 2021/01/07 11:21:25 by braimbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_redirection	*init_redirection(t_token *token)
{
	t_redirection *redirection;

	redirection = malloc(sizeof(t_redirection));
	redirection->type = token->type;
	redirection->filename = token->next->str;
	redirection->brother = NULL;
	return (redirection);
}

void connect_links(t_redirection **redirection_start,
		t_redirection ** redirection_current, t_redirection *redirection)
{
	if (!(*redirection_start))
		*redirection_start = redirection;
	else
	{
		while ((*redirection_current) && (*redirection_current)->brother)
			*redirection_current = (*redirection_current)->brother;
		(*redirection_current)->brother = redirection;
	}
}

t_redirection	*parse_redirection(t_token *token, t_token *max, int *ec)
{
	t_redirection	*redirection_start;
	t_redirection	*redirection;
	t_redirection	*redirection_current;

	redirection_start = NULL;
	while (token && token != max)
	{
		if (token->type >= LESS)
		{
			if (!token->next || token->next->type >= LESS)
			{
				print_error(ec, 17);
				return (redirection_start);
			}
			redirection = init_redirection(token);
			redirection_current = redirection_start;
			connect_links(&redirection_start, &redirection_current, redirection);
			token = token->next;
		}
		token = token->next;
	}
	return (redirection_start);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raimbaultbrieuc <marvin@42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 16:34:28 by raimbault         #+#    #+#             */
/*   Updated: 2020/12/21 14:28:51 by braimbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_redirection	*malloc_fill_redirection(t_token *token)
{
	t_redirection *redirection;

	redirection = malloc(sizeof(t_redirection));
	redirection->type = token->type;
	redirection->filename = token->next->str;
	redirection->brother = NULL;
	return (redirection);
}

t_redirection	*append_redirection(t_redirection *redirection_c,
		t_redirection *redirection)
{
	while (redirection_c && redirection_c->brother)
		redirection_c = redirection_c->brother;
	redirection_c->brother = redirection;
	return (redirection_c);
}

t_redirection	*parse_redirection(t_token *token, t_token *max, int *ec)
{
	t_redirection	*redirection_start;
	t_redirection	*redirection;
	t_redirection	*redirection_c;

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
			redirection = malloc_fill_redirection(token);
			redirection_c = redirection_start;
			if (!redirection_start)
				redirection_start = redirection;
			else
				redirection_c = append_redirection(redirection_c, redirection);
			token = token->next;
		}
		token = token->next;
	}
	return (redirection_start);
}

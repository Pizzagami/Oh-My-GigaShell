/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raimbaultbrieuc <marvin@42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 16:34:28 by raimbault         #+#    #+#             */
/*   Updated: 2020/09/21 15:44:11 by braimbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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
			if (!token->next)
			{
				print_error("Error : Missing file after redirection\n", ec, 2513);
				return (redirection_start);
			}
			if (token->next->type >= LESS)
			{
				print_error("Error : Missing file after redirection\n", ec, 2513);
				return (redirection_start);
			}
			redirection = malloc(sizeof(t_redirection));
			redirection->type = token->type;
			redirection->filename = token->next->str;
			redirection->brother = NULL;
			redirection_current = redirection_start;
			if (!redirection_start)
				redirection_start = redirection;
			else
			{
				while (redirection_current && redirection_current->brother)
					redirection_current = redirection_current->brother;
				redirection_current->brother = redirection;
			}
			token = token->next;
		}
		token=token->next;
	}
	return (redirection_start);
}

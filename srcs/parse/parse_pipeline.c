/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raimbaultbrieuc <marvin@42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 16:33:07 by raimbault         #+#    #+#             */
/*   Updated: 2020/12/04 13:50:49 by braimbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_pipeline	*parse_pipeline2(int *ec, t_token *start, t_token *max)
{
	t_pipeline *pipeline;

	if (!start || start == max)
		return (NULL);
	pipeline = malloc(sizeof(t_pipeline));
	if (pipeline == NULL)
	{
		print_error(ec, 10);
		return (NULL);
	}
	pipeline->brother = NULL;
	pipeline->command = NULL;
	return (pipeline);
}

t_pipeline	*parse_pipeline(t_token *start, t_token *max, int *ec)
{
	t_pipeline	*pipeline;
	t_token		*token;
	t_token		*tmp;

	pipeline = parse_pipeline2(ec, start, max);
	if (pipeline == NULL)
		return (pipeline);
	if (start && start->type == PIPE)
	{
		print_error(ec, 11);
		return (pipeline);
	}
	token = start;
	while (token && token != max && (token->type != PIPE ||
			is_in_brackets(token, start)))
		token = token->next;
	pipeline->command = (parse_command(start, token, ec));
	tmp = token;
	if (token && token->type == PIPE)
		token = token->next;
	pipeline->brother = parse_pipeline(token, max, ec);
	if (pipeline->brother == NULL && tmp && tmp->type == PIPE)
		print_error(ec, 12);
	return (pipeline);
}

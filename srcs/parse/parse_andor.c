/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_andor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raimbaultbrieuc <marvin@42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 16:31:43 by raimbault         #+#    #+#             */
/*   Updated: 2021/02/15 11:22:33 by braimbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_andor	*parse_andor2(t_andor *andor, int *ec, t_token *token, t_token *max)
{
	andor->type = VOID;
	if (token && (token->type == AND_IF || token->type == OR_IF)
		&& token != max)
	{
		andor->type = token->type;
		token = token->next;
	}
	if (*ec == 0)
		andor->brother = parse_andor(token, max, ec);
	if (andor->brother == NULL && andor->type && *ec == 0)
	{
		printf("YO\n");
		print_error(ec, (token) ? 19 : 7);
		return (andor);
	}
	return (andor);
}

t_andor	*init_andor(void)
{
	t_andor *andor;

	andor = malloc(sizeof(t_andor));
	andor->brother = NULL;
	andor->pipeline = NULL;
	return (andor);
}

t_andor	*parse_andor(t_token *start, t_token *max, int *ec)
{
	t_andor	*andor;
	t_token *token;

	if (!start || start == max)
		return (NULL);
	andor = init_andor();
	if (andor == NULL)
	{
		print_error(ec, 8);
		return (NULL);
	}
	if (start && (start->type == AND_IF || start->type == OR_IF ||
		start->type == AND))
	{
		print_error(ec, 9);
		return (andor);
	}
	token = start;
	while (token && token != max && ((token->type != AND_IF &&
			token->type != OR_IF) || is_in_brackets(token, start)))
		token = token->next;
	andor->pipeline = (parse_pipeline(start, token, ec));
	andor = parse_andor2(andor, ec, token, max);
	return (andor);
}

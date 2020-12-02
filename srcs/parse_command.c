/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raimbaultbrieuc <marvin@42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 16:33:43 by raimbault         #+#    #+#             */
/*   Updated: 2020/12/02 15:37:49 by braimbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int			brackets_error(t_token **token, t_token *start, t_token *max,
							int *ec)
{
	if (!*token)
	{
		print_error("Error : Missing closing paranthesis\n", ec, 2525);
		return (1);
	}
	if ((*token)->type == CBRA)
	{
		print_error("Error : Void paranthesis\n", ec, 2536);
		return (1);
	}
	while (*token && is_in_brackets(*token, start) && *token != max)
		*token = (*token)->next;
	if (!(*token))
	{
		print_error("Error : Missing closing paranthesis\n", ec, 2525);
		return (1);
	}
	if (double_brackets(start->next, *token))
	{
		print_error("Error : Way too much paranthesis\n", ec, 2536);
		return (1);
	}
	return (0);
}

t_command	*malloc_to_null(void)
{
	t_command *command;

	command = malloc(sizeof(t_command));
	command->instruction = NULL;
	command->redirection = NULL;
	command->c_list = NULL;
	return (command);
}

t_command	*parse_command(t_token *start, t_token *max, int *ec)
{
	t_command		*command;
	t_token			*token;

	if (!start || start == max)
		return (NULL);
	command = malloc_to_null();
	token = start;
	if (token->type == CBRA)
	{
		print_error("Error : Missing opening paranthesis\n", ec, 2524);
		return (command);
	}
	if (token->type == OBRA)
	{
		token = token->next;
		if (!brackets_error(&token, start, max, ec))
			command->c_list = parse_list(start->next, token, ec);
		return (command);
	}
	while (token && token != max)
		token = token->next;
	command->redirection = parse_redirection(start, token, ec);
	command->instruction = parse_instruction(start, token, ec);
	return (command);
}

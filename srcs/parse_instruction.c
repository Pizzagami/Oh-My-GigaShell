/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_instruction.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raimbaultbrieuc <marvin@42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 16:35:12 by raimbault         #+#    #+#             */
/*   Updated: 2020/12/08 14:16:10 by braimbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_instruction	*parse_instruction(t_token *start, t_token *max, int *ec)
{
	t_instruction	*instruction;
	t_token			*token;

	instruction = malloc(sizeof(t_instruction));
	instruction->start = start;
	instruction->max = max;
	token = start;
	while (token && token != max)
	{
		if (token->type == OBRA)
		{
			print_error(ec, 13);
			break;
		}
		if (token->type == CBRA)
		{
			print_error(ec, 16);
			break;
		}		token = token->next;
	}
	return (instruction);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_instruction.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raimbaultbrieuc <marvin@42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 16:35:12 by raimbault         #+#    #+#             */
/*   Updated: 2020/09/21 15:33:57 by braimbau         ###   ########.fr       */
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
		if (token->type == OBRA || token->type == CBRA)
		{
			print_error("Error : Parsing error near unexepected token\n\r", ec, 2736);
		}
		token = token->next;
	}
	return (instruction);
}

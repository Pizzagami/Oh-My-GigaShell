/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raimbaultbrieuc <marvin@42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 14:45:18 by raimbault         #+#    #+#             */
/*   Updated: 2020/12/22 07:06:21 by braimbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	display_andor(t_andor *andor, int i)
{
	int x;

	x = 0;
	while (x < i)
	{
		printf(".  ");
		x++;
	}
	printf("ANDOR\n");
	if (andor->pipeline)
		display_pipeline(andor->pipeline, i + 1);
	if (andor->brother)
		display_andor(andor->brother, i);
}

void	display_pipeline(t_pipeline *pipeline, int i)
{
	int x;

	x = 0;
	while (x < i)
	{
		printf(".  ");
		x++;
	}
	printf("PIPELINE\n");
	if (pipeline->command)
		display_command(pipeline->command, i + 1);
	if (pipeline->brother)
		display_pipeline(pipeline->brother, i);
}

void	display_command(t_command *command, int i)
{
	int x;

	x = 0;
	while (x < i)
	{
		printf(".  ");
		x++;
	}
	printf("COMMAND\n");
	if (command->redirection)
		display_redirection(command->redirection, i + 1);
	if (command->instruction)
		display_instruction(command->instruction, i + 1);
	if (command->c_list)
		display_list(command->c_list, i + 1);
}

void	display_redirection(t_redirection *redirection, int i)
{
	int x;

	x = 0;
	while (x < i)
	{
		printf(".  ");
		x++;
	}
	printf("REDIRECTION");
	while (redirection)
	{
		printf(" %d : %s |", redirection->type, redirection->filename);
		redirection = redirection->brother;
	}
	printf("\n");
}

void	display_instruction(t_instruction *instruction, int i)
{
	int		x;
	t_token	*start;
	t_token	*max;

	start = instruction->start;
	max = instruction->max;
	x = 0;
	while (x < i)
	{
		printf(".  ");
		x++;
	}
	printf("INSTRUCTION");
	while (start && start != max)
	{
		printf(" %s", (start->str) ? start->str : "VOID");
		start = start->next;
	}
	printf("\n");
}

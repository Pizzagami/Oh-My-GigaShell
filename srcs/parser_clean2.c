/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_clean2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raimbaultbrieuc <marvin@42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 14:53:41 by raimbault         #+#    #+#             */
/*   Updated: 2020/12/22 07:14:22 by braimbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	clean_instruction(t_instruction *instruction)
{
	(void)instruction;
}

void	clean_command(t_command *command)
{
	if (command->c_list)
	{
		clean_list(command->c_list);
		free(command->c_list);
	}
	if (command->instruction)
	{
		clean_instruction(command->instruction);
		free(command->instruction);
	}
	if (command->redirection)
		clean_redirection(command->redirection);
}

void	clean_redirection(t_redirection *redirection)
{
	if (redirection->brother)
		clean_redirection(redirection->brother);
	free(redirection);
}

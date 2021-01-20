/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braimbau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 09:33:39 by braimbau          #+#    #+#             */
/*   Updated: 2021/01/20 09:34:03 by braimbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

void	heredoc_command(t_command *command, int *ec)
{
	if (command->c_list)
		heredoc_list(command->c_list, ec);
	if (command->redirection && command->redirection->type == DLESS)
		set_heredoc(command->redirection, ec);
}

void	heredoc_pipeline(t_pipeline *pipeline, int *ec)
{
	if (pipeline->brother)
		heredoc_pipeline(pipeline->brother, ec);
	if (pipeline->command)
		heredoc_command(pipeline->command, ec);
}

void	heredoc_andor(t_andor *andor, int *ec)
{
	if (andor->brother)
		heredoc_andor(andor->brother, ec);
	if (andor->pipeline)
		heredoc_pipeline(andor->pipeline, ec);
}

void	heredoc_list(t_list *list, int *ec)
{
	if (list->brother)
		heredoc_list(list->brother, ec);
	if (list->andor)
		heredoc_andor(list->andor, ec);
}

void	heredoc_input(t_input *input, int *ec)
{
	if (input && input->list)
		heredoc_list(input->list, ec);
}

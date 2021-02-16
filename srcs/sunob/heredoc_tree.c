/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selgrabl <selgrabl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 09:33:39 by braimbau          #+#    #+#             */
/*   Updated: 2021/02/15 10:36:18 by braimbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

void	heredoc_command(t_command *command, int *ec)
{
	t_redirection *redirection;

	redirection = command->redirection;
	if (command->c_list)
		heredoc_list(command->c_list, ec);
	while (redirection)
	{
		if (redirection->type == DLESS)
			set_heredoc(redirection, ec, 0, NULL);
		redirection = redirection->brother;
	}
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

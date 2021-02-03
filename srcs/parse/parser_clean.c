/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_clean.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raimbaultbrieuc <marvin@42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 14:54:16 by raimbault         #+#    #+#             */
/*   Updated: 2021/02/03 09:49:17 by braimbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	clean_pipeline(t_pipeline *pipeline)
{
	if (pipeline->brother)
	{
		clean_pipeline(pipeline->brother);
		free(pipeline->brother);
	}
	if (pipeline->command)
	{
		clean_command(pipeline->command);
		free(pipeline->command);
	}
}

void	clean_andor(t_andor *andor)
{
	if (andor->brother)
	{
		clean_andor(andor->brother);
		free(andor->brother);
	}
	if (andor->pipeline)
	{
		clean_pipeline(andor->pipeline);
		free(andor->pipeline);
	}
}

void	clean_list(t_list *list)
{
	if (list->brother)
	{
		clean_list(list->brother);
		free(list->brother);
	}
	if (list->andor)
	{
		clean_andor(list->andor);
		free(list->andor);
	}
}

void	clean_input(t_input *input)
{
	if (input && input->list)
	{
		clean_list(input->list);
		free(input->list);
	}
	if (input)
		free(input);
}

void	clean_token_list(t_token *token)
{
	if (token)
	{
		clean_token_list(token->next);
		if (token->str)
			free(token->str);
		free(token);
	}
}

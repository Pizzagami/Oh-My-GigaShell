/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raimbaultbrieuc <marvin@42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 14:44:24 by raimbault         #+#    #+#             */
/*   Updated: 2020/09/21 15:50:55 by braimbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int		exec_input(t_input *input, t_omm omm)
{
	if (input == NULL)
		return (0);
	return (exec_list(input->list, omm));
}

int	exec_list(t_list *list, t_omm omm)
{
	int i;

	i = 0;
	if (list->andor)
		i = exec_andor(list->andor, omm);
	if (list->brother)
		i = exec_list(list->brother, omm);
	return (i);
}

char **create_tab(t_token *start, t_token *max)
{
	t_token *token;
	int i;
	char **tab;

	i = 0;
	token = start;
	while (token && token != max)
	{
		if (token->type >= LESS)
			i -= 2;
		token = token->next;
		i++;
	}
	tab = malloc(sizeof(char *) * (i + 1));
	token = start;
		i = 0;
	while (token && token != max)
	{
		if (token->type >= LESS)
		{
			token = token->next;
			if (token == max)
				token = NULL;
			token = token->next;
		}
		else
		{
			tab[i] = token->str;
			i++;
			token = token->next;
		}
	}
	tab[i] = NULL;
	return (tab);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raimbaultbrieuc <marvin@42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 16:30:25 by raimbault         #+#    #+#             */
/*   Updated: 2020/12/04 13:52:16 by braimbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_list	*parse_list(t_token *start, t_token *max, int *ec)
{
	t_list	*list;
	t_token	*token;

	list = NULL;
	if (!start || start == max)
		return (NULL);
	list = malloc(sizeof(t_list));
	list->andor = NULL;
	list->brother = NULL;
	if (list == NULL)
	{
		print_error(ec, 5);
		return (NULL);
	}
	token = start;
	if (start && start->type == SEMI && token != max)
	{
		print_error(ec, 6);
		return (list);
	}
	while (token && token != max && (token->type != SEMI ||
			is_in_brackets(token, start)))
		token = token->next;
	list->andor = parse_andor(start, token, ec);
	if (token && token != max && token->type == SEMI)
		token = token->next;
	list->brother = parse_list(token, max, ec);
	return (list);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raimbaultbrieuc <marvin@42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 16:30:25 by raimbault         #+#    #+#             */
/*   Updated: 2021/01/07 10:58:59 by braimbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_list	*init_list(int *ec)
{
	t_list *list;

	list = NULL;
	list = malloc(sizeof(t_list));
	list->andor = NULL;
	list->brother = NULL;
	if (list == NULL)
	{
		print_error(ec, 5);
		return (NULL);
	}
	return (list);
}

t_list	*parse_list(t_token *start, t_token *max, int *ec)
{
	t_list	*list;
	t_token	*token;

	if (!start || start == max)
		return (NULL);
	list = init_list(ec);
	if (list == NULL)
		return (NULL);
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

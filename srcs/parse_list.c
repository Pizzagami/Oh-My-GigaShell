/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raimbaultbrieuc <marvin@42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 16:30:25 by raimbault         #+#    #+#             */
/*   Updated: 2020/09/21 10:44:39 by braimbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_list	*parse_list(t_token *start, t_token *max, int *ec)
{
	t_list	*list;
	t_token	*token;

	//printf("START = %d\n", start->type);
	list = NULL;
	if (!start || start == max)
		return (NULL);
	list = malloc(sizeof(t_list));
	if (list == NULL)
	{
		print_error("Malloc error\n", ec, 12);
		return (NULL);
	}
	token = start;
	if (start && start->type == SEMI && token != max)
	{
		print_error("Error : Missing element(s) before semicolon\n", ec, 2200);
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

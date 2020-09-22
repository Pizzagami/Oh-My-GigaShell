/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raimbaultbrieuc <marvin@42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 16:23:29 by raimbault         #+#    #+#             */
/*   Updated: 2020/07/31 11:10:15 by braimbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int		double_brackets(t_token *start, t_token *max)
{
	int i;

	i = 0;
	while (start)
	{
		if (start->type == OBRA)
			i++;
		if (start->type == CBRA)
			i--;
		if (start->next == max)
			return (1);
		if (i < 1)
			return (0);
		start = start->next;
	}
	return (1);
}

void	*print_error(char *str, int *ec, int error)
{
	printf("%s", str);
	*ec = error;
	return (NULL);
}

int		is_in_brackets(t_token *token, t_token *start)
{
	int i;

	i = 0;
	while (start)
	{
		if (start->type == OBRA)
			i++;
		if (start->type == CBRA)
			i--;
		if (start == token)
			return (i);
		start = start->next;
	}
	return (0);
}

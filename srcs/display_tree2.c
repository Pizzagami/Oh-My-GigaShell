/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_tree2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raimbaultbrieuc <marvin@42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 14:44:24 by raimbault         #+#    #+#             */
/*   Updated: 2020/07/16 15:12:01 by raimbaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	display_input(t_input *input, int i)
{
	int x;

	x = 0;
	while (x < i)
	{
		printf(".  ");
		x++;
	}
	printf("INPUT\n");
	if (input->list)
		display_list(input->list, i + 1);
}

void	display_list(t_list *list, int i)
{
	int x;

	x = 0;
	while (x < i)
	{
		printf(".  ");
		x++;
	}
	printf("LIST\n");
	if (list->andor)
		display_andor(list->andor, i + 1);
	if (list->brother)
		display_list(list->brother, i);
}

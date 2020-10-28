/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raimbaultbrieuc <marvin@42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 16:23:04 by raimbault         #+#    #+#             */
/*   Updated: 2020/10/28 15:38:25 by braimbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_input	*parse_input(t_token *start, int *ec)
{
	t_input	*input;
	
	if (start == NULL)
		return (NULL);
	input = malloc(sizeof(t_input));
	if (input == NULL)
	{
		print_error("Malloc error\n", ec, 11);
		return (NULL);
	}
	input->list = parse_list(start, NULL, ec);
	return (input);
}

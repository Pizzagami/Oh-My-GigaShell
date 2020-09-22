/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raimbaultbrieuc <marvin@42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 15:24:37 by raimbault         #+#    #+#             */
/*   Updated: 2020/09/21 16:13:59 by braimbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h"

int		persecutor(t_hist *hist, t_arrow *ar, char *env[])
{
	t_token	*token_start;
	t_token *tmp;
	t_input	*tree;
	int		ec;

	ar->x = 0;
	ec = ar->x;
	ec = 0;
	token_start = create_token_list(hist->tab[0], &ec);
	if (ec)
	{
		printf("Missing closing double quote\n\r");
		clean_token_list(token_start);
		return (ec);
	}
	tmp = token_start;
	token_start = token_start->next; //ultra bancal et pas leaks proof
	free(tmp);
	tree = parse_input(token_start, &ec);
	//printf_token(token_start);
	if (!ec)
	{
		//display_input(tree, 0);
		exec_input(tree, init_std_fd(env));
	}
	clean_input(tree);
	clean_token_list(token_start);
	return (ec);
}

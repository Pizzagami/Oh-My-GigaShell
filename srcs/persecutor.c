/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   persecutor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raimbaultbrieuc <marvin@42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 15:24:37 by raimbault         #+#    #+#             */
/*   Updated: 2020/11/03 13:47:50 by braimbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h"

int		persecutor(t_hist *hist, t_arrow *ar, char *env[], int *last_ret)
{
	t_token	*token_start;
	char	*home;
	t_input	*tree;
	int		ec;

	ar->x = 0;
	ec = ar->x;
	ec = 0;
	token_start = create_token_list(hist->tab[0], &ec);
	if (ec)
	{
		printf("Missing closing double quote\n");
		clean_token_list(token_start);
		return (ec);
	}
	home = get_env(env, "HOME");
	token_start = starize_list(token_start, home);
	free(home);
	//printf_token(token_start);
	tree = parse_input(token_start, &ec);
	if (!ec)
	{
		//display_input(tree, 0);
		exec_input(tree, init_std_fd(env, last_ret));
	}
	else
		*last_ret = ec;
	clean_input(tree);
	clean_token_list(token_start);
	return (ec);
}

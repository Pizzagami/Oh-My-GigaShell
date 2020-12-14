/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   persecutor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raimbaultbrieuc <marvin@42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 15:24:37 by raimbault         #+#    #+#             */
/*   Updated: 2020/12/13 19:57:59 by braimbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h"

int		persecutor(t_hist *hist, t_env *env, int *last_ret)
{
	t_token	*token_start;
	t_input	*tree;
	int		ec;
	char *quot;
	char *str;

	ec = 0;
	str = ft_strdup(hist->tab[0]);
	quot = quote_string(&str, &ec);
	if (ec)
	{
		free(str);
		free(quot);
		return (print_error(&ec, ec));
	}
	token_start = create_token_list(str, quot);
	//printf_token(token_start);
	tree = parse_input(token_start, &ec);
	if (!ec)
	{
		//display_input(tree, 0)
		exec_input(tree, init_std_fd(env, last_ret));
	}
	else
		*last_ret = ec;
	free(quot);
	free(str);
	clean_input(tree);
	clean_token_list(token_start);
	return (ec);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   persecutor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raimbaultbrieuc <marvin@42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 15:24:37 by raimbault         #+#    #+#             */
/*   Updated: 2021/01/31 14:29:01 by braimbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h"

int		persecutor(t_hist *hist, t_env *env, int *last_ret)
{
	t_token	*token_start;
	t_input	*tree;
	int		ec;
	char	*quot;
	char	*str;

	ec = 0;
	str = ft_strdup(hist->tab[0]);
	quot = quote_string(&str, &ec);
	if (ec)
		mfree(str, quot);
	if (ec)
		return (print_error(&ec, ec));
	token_start = create_token_list(str, quot);
	tree = parse_input(token_start, &ec);
	if (!ec)
		heredoc_input(tree, &ec);
	if (!ec)
		exec_input(tree, init_std_fd(env, last_ret));
	else
		*last_ret = ec;
	mfree(quot, str);
	clean_input(tree);
	clean_token_list(token_start);
	return (ec);
}

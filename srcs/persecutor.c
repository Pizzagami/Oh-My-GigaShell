/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   persecutor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raimbaultbrieuc <marvin@42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 15:24:37 by raimbault         #+#    #+#             */
/*   Updated: 2020/11/05 10:54:17 by braimbau         ###   ########.fr       */
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
	char *quot;
	char *str;

	ar->x = 0;
	ec = ar->x;
	ec = 0;
	str = ft_strdup(hist->tab[0]);
	quot = quote_string(str, &ec);
	if (ec)
	{
		printf("Missong clothing quote, dquote or error with backslash\n");
		return (ec);
	}
	token_start = create_token_list(str, quot);
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

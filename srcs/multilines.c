/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multilines.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braimbau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 10:49:12 by braimbau          #+#    #+#             */
/*   Updated: 2020/12/09 14:16:16 by braimbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int multilines(t_hist *hist, t_env *env, int *last_ret, t_multi	*multi)
{
	printf("+\n");
	int		ret;
	char	*tmp;

	ret = 0;
	if (multi->type != 0)
	{
		tmp = hist->tab[0];
		hist->tab[0] = ft_strjoin_sep(multi->str, hist->tab[0], '\n');
		free(tmp);
		free(multi->str);
		multi->type = 0;
	}
	ret = persecutor(hist, env, last_ret);
	if (ret == 1)
	{
		multi->str = ft_strdup(hist->tab[0]);
		multi->type = ret;
	}
	return(ret);
}

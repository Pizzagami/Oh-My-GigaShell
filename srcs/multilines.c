/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multilines.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braimbau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 10:49:12 by braimbau          #+#    #+#             */
/*   Updated: 2020/12/08 15:55:20 by braimbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int multilines(t_hist *hist, t_env *env, int *last_ret, char **ml)
{
	int		ret;
	char	*tmp;

	ret = 0;
	if (*ml != 0)
	{
		tmp = hist->tab[0];
		hist->tab[0] = ft_strjoin_sep(*ml, hist->tab[0], '\n');
		free(tmp);
		free(*ml);
		*ml = NULL;
	}
	ret = persecutor(hist, env, last_ret);
	if (ret == 1)
		*ml = ft_strdup(hist->tab[0]);
	return(ret);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multilines.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pizzagami <pizzagami@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 10:49:12 by braimbau          #+#    #+#             */
/*   Updated: 2021/01/12 10:50:08 by braimbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	multilines(t_hist *hist, t_env *env, int *last_ret, t_multi *multi)
{
	int		ret;
	char	*tmp;

	ret = 0;
	if (multi->type != 0 && multi->x != 0)
	{
		tmp = hist->tab[0];
		hist->tab[0] = ft_strjoin_sep(multi->str, hist->tab[0], '\n');
		free(tmp);
		free(multi->str);
		multi->type = 0;
	}
	if (multi->x == 0)
		hist->tab[0] = (multi->type) ?
		ft_strjoin_sep(multi->str, "", '\n') : "";
	ret = persecutor(hist, env, last_ret);
	if (ret == 1 || ret == 2 || ret == 7 || ret == 12 || ret == 13)
	{
		multi->str = ft_strdup(hist->tab[0]);
		multi->type = ret;
		return (ret);
	}
	return (0);
}

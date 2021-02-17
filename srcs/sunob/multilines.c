/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multilines.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braimbau <braimbau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 10:49:12 by braimbau          #+#    #+#             */
/*   Updated: 2021/02/17 15:54:27 by braimbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		multilines(t_hist *hist, t_env *env, int *last_ret, t_multi *multi)
{
	int ret;

	(void)multi;
	ret = persecutor(hist, env, last_ret);
	if (ret == 1 || ret == 2 || ret == 7 || ret == 12 || ret == 13)
		return (1);
	else if (ret > 1)
		*last_ret = 258;
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_gestion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braimbau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 15:03:37 by braimbau          #+#    #+#             */
/*   Updated: 2020/10/27 15:59:41 by braimbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_omm	init_std_fd(char **env, int *last_ret)
{
	t_omm omm;
	
	omm.env = env;
	omm.stdin = dup(0);
	omm.stdout = dup(1);
	omm.last_ret = last_ret;
	return (omm);
}

void	reset_fd(t_omm omm)
{
		if (1)
			dup2(omm.stdout, 1);
		if (1)
			dup2(omm.stdin, 0);
}

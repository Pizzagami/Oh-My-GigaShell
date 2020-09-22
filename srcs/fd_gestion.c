/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_gestion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braimbau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 15:03:37 by braimbau          #+#    #+#             */
/*   Updated: 2020/09/14 09:48:25 by braimbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_omm	init_std_fd(char **env)
{
	t_omm omm;
	
	omm.env = env;
	omm.stdin = dup(0);
	omm.stdout = dup(1);
	return (omm);
}

void	reset_fd(t_omm omm)
{
		if (1)
			dup2(omm.stdout, 1);
		if (1)
			dup2(omm.stdin, 0);
}

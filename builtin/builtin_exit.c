/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braimbau <braimbau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 10:23:00 by selgrabl          #+#    #+#             */
/*   Updated: 2021/02/10 15:33:56 by braimbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_exit(t_env *env, char **str)
{
	int j;
	int ret;

	j = 0;
	ret = 0;
	if (!(str && str[0]))
		ft_putstr_fd("exit\n", 2);
	else if (ft_isalpha(str[0][j]))
		{
			ft_putstr_fd("exit \nbash: exit: ", 2);
			ft_putstr_fd(*str, 2);
			ft_putstr_fd(" numeric argument required\n", 2);
		}
	else
	{
		if (str[0][0] == '-')
		{
			ret = -1;
			j++;
		}
		while (str[0][j])
		{
			if (ft_isdigit(str[0][j]))
				j++;
			else
				{
					ft_putstr_fd("exit \nbash: exit: ", 2);
					ft_putstr_fd(*str, 2);
					ft_putstr_fd(" numeric argument required\n", 2);
					exit (255);
				}
			ret *= ft_atoi(str[0]);
		}
		if (str[1] && str[1][0])
		{
			ft_putstr_fd("exit: too many arguments", 2);
			return ;
		}
	}
	free_env(env);
	exit(ret);
}

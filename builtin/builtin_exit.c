/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pizzagami <pizzagami@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 10:23:00 by selgrabl          #+#    #+#             */
/*   Updated: 2021/02/11 20:50:28 by pizzagami        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
void numerror(char *str)
{
	ft_putstr_fd("exit \nbash: exit: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(" numeric argument required\n", 2);
}

void whilerror(char **str, int *j, t_env *env, int *ret)
{
	if (ft_isdigit(str[0][*j]))
		*j++;
	else
		{
			numerror(*str);
			free_env(env);
			exit (255);
		}
	ret = (ret >= 0) ? ft_atoi(str[0]) % 255: 256 - (ft_atoi(str[0]) % 255) ;
}

void	builtin_exit(t_env *env, char **str)
{
	int j;
	int ret;

	j = 0;
	ret = 0;
	if (!(str && str[0]))
		ft_putstr_fd("exit\n", 2);
	else if (ft_isalpha(str[0][j]))
		numerror(*str);
	else
	{
		if (str[0][0] == '-')
		{
			ret = -1;
			j++;
		}
		while (str[0][j])
			whilerror(str, &j, env, &ret);
		if (str[1] && str[1][0])
			return (ft_putstr_fd("exit: too many arguments", 2));
	}
	free_env(env);
	exit(ret);
}

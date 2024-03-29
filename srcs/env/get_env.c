/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selgrabl <selgrabl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 14:53:54 by braimbau          #+#    #+#             */
/*   Updated: 2021/01/27 16:59:44 by selgrabl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*get_env(t_env *env, char *key)
{
	while (env)
	{
		if (ft_strcmp(env->name, key) == 0)
		{
			return (env->val);
		}
		env = env->next;
	}
	return (NULL);
}

char	**get_env2(t_env *env, char *key)
{
	while (env)
	{
		if (ft_strcmp(env->name, key) == 0)
		{
			return (&(env->val));
		}
		env = env->next;
	}
	return (NULL);
}

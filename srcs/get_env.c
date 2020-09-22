/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braimbau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 14:53:54 by braimbau          #+#    #+#             */
/*   Updated: 2020/07/31 11:16:18 by braimbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "parser.h"

char *get_env(char**env, char *key)
{
	int i;
	char *str;

	i = 0;
	while (env[i])
	{
		str = ft_substr(env[i], 0, ft_strfind(env[i], '='));
		if (strcmp(str, key) == 0)
		{
			free(str);
			return (ft_substr(env[i], ft_strfind(env[i], '=') + 1,
					ft_strlen(env[i]) - ft_strfind(env[i], '=')));
		}
		free(str);
		i++;
	}
	return (NULL);
}

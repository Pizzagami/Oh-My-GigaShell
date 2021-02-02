/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selgrabl <selgrabl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 11:29:21 by braimbau          #+#    #+#             */
/*   Updated: 2021/02/02 15:25:19 by selgrabl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"
#include "libft.h"

int		split_verif(char *str, int *y)
{
	int i;
	int ret;

	ret = 0;
	i = 0;
	if (str[0] == '=' || (str[i] >= '0' && str[i] <= '9'))
		return (-1);
	while (str && str[i] != '=')
	{
		if (((str[i] > 47 && str[i] < 58) && i > 0) ||
				(str[i] > 96 && str[i] < 123)
		|| (str[i] > 64 && str[i] < 91) || str[i] == '_' ||
		(str[i] >= '0' && str[i] <= '9'))
			i++;
		else if (!str[i])
		{
			ret = 2;
			break ;
		}
		else
			return (-1);
	}
	*y = i;
	return (ret);
}

void	env_val(char *str, char **str1, int i, int j)
{
	int x;

	x = 0;
	i++;
	j++;
	while (str[i])
		i++;
	*str1 = malloc(sizeof(char) * (i - j + 1));
	(*str1)[i - j] = 0;
	while (j < i)
	{
		(*str1)[x] = str[j];
		x++;
		j++;
	}
}

int		env_split(char *str, char **name, char **val)
{
	int		i;
	int		j;
	int		ret;
	char	*str1;

	i = 0;
	j = 0;
	ret = 0;
	ret = split_verif(str, &i);
	if (ret < 0)
		return (ret);
	str1 = malloc(sizeof(char) * (i + 1));
	str1[i] = 0;
	while (j < i)
	{
		str1[j] = str[j];
		j++;
	}
	*name = ft_strdup(str1);
	free(str1);
	if (ret != 2)
		env_val(str, val, i, j);
	else
		*val = NULL;
	return (ret);
}

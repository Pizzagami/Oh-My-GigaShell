/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braimbau <braimbau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 16:23:58 by selgrabl          #+#    #+#             */
/*   Updated: 2021/02/10 15:13:32 by braimbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int i;
	int k;
	int j;

	i = 0;
	k = 1;
	j = 0;
	while (str[i] == '\n' || str[i] == '\t' || str[i] == '\v' || str[i] == '\r'
		|| str[i] == '\f' || str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			k = -k;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		j = j * 10 + str[i] - '0';
		i++;
	}
	return (k * j);
}

int	ft_atoi2(const char *str)
{
	int i;
	int k;
	int j;

	i = 0;
	k = 1;
	j = 0;
	while (str[i] == '\n' || str[i] == '\t' || str[i] == '\v' || str[i] == '\r'
		|| str[i] == '\f' || str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			k = -k;
		i++;
	}
	while (str[i])
	{
		if (ft_isdigit(str[i]))
		{
			j = j * 10 + str[i] - '0';
			i++;
		}
		else
			return (-42);
	}
	return (k * j);
}
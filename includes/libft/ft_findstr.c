/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_findstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selgrabl <selgrabl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 14:22:43 by selgrabl          #+#    #+#             */
/*   Updated: 2020/10/28 11:00:39 by braimbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

int	ft_findstr(char *str, char *to_find)
{
	int i;
	int j;
	int n;

	int len = ft_strlen(str);
	i = 0;
	j = 0;
	n = 0;
	while (to_find[n] != '\0')
		n++;
	if (n == 0)
		return (0);
	while (str && str[i])
	{
		while (to_find[j] == str[i + j] && i + j < len)
		{
			if (j == n - 1)
				return (i);
			j++;
		}
		j = 0;
		i++;
	}
	return (-1);
}

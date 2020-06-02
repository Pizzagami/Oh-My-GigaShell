/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selgrabl <selgrabl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 14:33:36 by braimbau          #+#    #+#             */
/*   Updated: 2019/10/19 13:04:15 by selgrabl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*str;
	long	i;
	long	s;

	i = 0;
	s = (long)(count * size);
	if (!(str = malloc(s * sizeof(char))))
		return (NULL);
	while (i < s)
	{
		str[i] = 0;
		i++;
	}
	return (str);
}

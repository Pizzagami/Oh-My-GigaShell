/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selgrabl <selgrabl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 18:40:07 by selgrabl          #+#    #+#             */
/*   Updated: 2019/10/15 19:22:17 by selgrabl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned int		i;
	unsigned char		*x;

	i = 0;
	x = (unsigned char *)s;
	while (i < n)
	{
		if (x[i] == (unsigned char)c)
			return ((void*)&x[i]);
		i++;
	}
	return (NULL);
}

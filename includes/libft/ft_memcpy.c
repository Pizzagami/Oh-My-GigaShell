/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selgrabl <selgrabl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 13:59:45 by braimbau          #+#    #+#             */
/*   Updated: 2019/10/19 12:18:52 by selgrabl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *restrict dst, const void *restrict src, size_t n)
{
	char *ds;
	char *sr;

	if (dst == NULL && src == NULL)
		return (NULL);
	ds = (char *)dst;
	sr = (char *)src;
	while (n > 0)
	{
		*ds = *sr;
		ds++;
		sr++;
		n--;
	}
	return (dst);
}

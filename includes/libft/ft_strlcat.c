/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selgrabl <selgrabl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 16:56:31 by selgrabl          #+#    #+#             */
/*   Updated: 2019/10/14 16:55:55 by selgrabl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *restrict dst, const char *restrict src, size_t size)
{
	size_t i;
	size_t j;
	size_t len;

	i = 0;
	while (dst[i])
		i++;
	len = i;
	j = 0;
	while (size > 0 && i < size - 1 && src[j])
		dst[i++] = src[j++];
	if (size > 0)
		dst[i] = 0;
	i = 0;
	while (src[i])
		i++;
	if (size < len)
		return (i + size);
	return (i + len);
}

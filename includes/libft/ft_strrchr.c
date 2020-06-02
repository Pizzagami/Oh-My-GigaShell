/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selgrabl <selgrabl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 14:15:17 by selgrabl          #+#    #+#             */
/*   Updated: 2019/10/18 17:30:18 by selgrabl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char *r;

	r = NULL;
	while (*s)
	{
		if (*s == c)
			r = (char *)s;
		s++;
	}
	if (c == 0)
		r = (char *)s;
	return (r);
}

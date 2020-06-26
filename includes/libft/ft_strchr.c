/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selgrabl <selgrabl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 14:14:14 by selgrabl          #+#    #+#             */
/*   Updated: 2019/10/18 17:11:49 by selgrabl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *chaine, int car)
{
	char *str;

	str = (char *)chaine;
	while (*str != car)
	{
		if (*str == '\0')
			return (NULL);
		str++;
	}
	return (str);
}

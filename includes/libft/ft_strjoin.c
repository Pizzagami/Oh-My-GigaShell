/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selgrabl <selgrabl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 18:30:44 by selgrabl          #+#    #+#             */
/*   Updated: 2020/11/29 20:36:45 by braimbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char			*ft_strcat(char *dest, char *src, int i)
{
	unsigned int j;

	j = 0;
	if (src == NULL)
		return (NULL);
	while (src[j] != '\0')
	{
		dest[i + j] = src[j];
		j++;
	}
	dest[i + j] = '\0';
	return (dest);
}

char			*ft_strcpy(char *dest, char *src)
{
	unsigned int i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	return (dest);
}

static int		ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str && str[i] != '\0')
		i++;
	return (i);
}

char			*ft_strjoin(const char *s1, const char *s2)
{
	int		i;
	int		j;
	char	*dest;
	char	*str1;
	char	*str2;

	str1 = (char *)s1;
	str2 = (char *)s2;
	i = ft_strlen(str1);
	j = ft_strlen(str2);
	dest = malloc(sizeof(char) * (i + j + 1));
	if (!dest)
		return (NULL);
	ft_strcpy(dest, str1);
	ft_strcat(dest, str2, i);
	dest[i + j] = '\0';
	return (dest);
}

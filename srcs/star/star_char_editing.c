/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   star_char_editing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braimbau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 13:06:07 by braimbau          #+#    #+#             */
/*   Updated: 2021/01/08 15:25:45 by braimbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*ft_strjoin_sep(char *s1, char *s2, char c)
{
	int		i;
	int		x;
	char	*dest;

	i = ft_strlen(s1) + ft_strlen(s2);
	dest = malloc(sizeof(char) * (i + 2));
	if (!dest)
		return (NULL);
	x = 0;
	while (s1 && s1[x])
	{
		dest[x] = s1[x];
		x++;
	}
	dest[x] = c;
	x++;
	i = 0;
	while (s2 && s2[i])
	{
		dest[x] = s2[i];
		x++;
		i++;
	}
	dest[x] = 0;
	return (dest);
}

char		*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	char			*ptr;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i])
		i++;
	if (!(ptr = malloc((len + 1) * sizeof(char))))
		return (NULL);
	if (i <= start)
	{
		ptr[0] = 0;
		return (ptr);
	}
	i = 0;
	while (i < len && s[start + i])
	{
		ptr[i] = s[start + i];
		i++;
	}
	ptr[i] = 0;
	return (ptr);
}

int			srcchar(char c, char *str)
{
	int x;

	x = 0;
	while (str[x])
	{
		if (str[x] == c)
			return (x);
		x++;
	}
	return (-1);
}

void		removechar(char **str, int x)
{
	while ((*str)[x + 1])
	{
		(*str)[x] = (*str)[x + 1];
		x++;
	}
	(*str)[x] = 0;
}

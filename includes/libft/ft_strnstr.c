/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selgrabl <selgrabl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 14:22:43 by selgrabl          #+#    #+#             */
/*   Updated: 2019/10/16 14:25:49 by selgrabl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strnstr(char *str, char *to_find, unsigned int len)
{
	unsigned int i;
	unsigned int j;
	unsigned int n;

	i = 0;
	j = 0;
	n = 0;
	while (to_find[n] != '\0')
		n++;
	if (n == 0)
		return (str);
	while (i < len)
	{
		while (to_find[j] == str[i + j] && i + j < len)
		{
			if (j == n - 1)
				return (str + i);
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}

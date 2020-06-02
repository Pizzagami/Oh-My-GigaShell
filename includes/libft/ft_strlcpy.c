/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selgrabl <selgrabl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 18:58:00 by selgrabl          #+#    #+#             */
/*   Updated: 2019/10/14 18:58:30 by selgrabl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

unsigned	int	ft_strlcpy(char *dest, char *src, unsigned int size)
{
	unsigned int i;

	if (!dest || !src)
		return (0);
	i = 0;
	while (size > 0 && i < (size - 1) && src[i])
	{
		dest[i] = src[i];
		i++;
	}
	if (size > 0)
		dest[i] = '\0';
	i = 0;
	while (src[i])
		i++;
	return (i);
}

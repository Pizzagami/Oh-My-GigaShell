/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selgrabl <selgrabl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 10:23:00 by selgrabl          #+#    #+#             */
/*   Updated: 2021/02/18 09:44:16 by braimbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include "libft.h"

void	buitin_echo(char **str)
{
	int n;
	int x;

	x = 0;
	n = 0;
	if (str && *str && ft_strcmp(*str, "-n") == 0)
	{
		n = 1;
		str++;
	}
	while (str && *str)
	{
		if (x > 0)
			ft_putstr(" ");
		ft_putstr(*str);
		str++;
		x++;
	}
	if (n == 0)
		write(1, "\n", 1);
}

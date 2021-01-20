/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bashy_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selgrabl <selgrabl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 11:00:35 by braimbau          #+#    #+#             */
/*   Updated: 2021/01/20 15:11:23 by selgrabl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	vleft(char c, char *str, int y)
{
	if (c != '\n')
		ft_putstr("\b");
	else
	{
		ft_putstr("\033[A");
		while ((str)[y] != '\n' && y > 0)
		{
			ft_putstr("\x1b[C");
			y--;
		}
		if (y == 0)
		{
			y = 11;
			while (y-- > 0)
				ft_putstr("\x1b[C");
		}
	}
}

void	vleft_ar(int x, t_arrow *ar, int len, char *str)
{
	int y;

	while (x > ar->x)
	{
		x--;
		if ((str)[len + x] != '\n')
			ft_putstr("\b");
		else
		{
			ft_putstr("\033[A");
			y = len + ar->x - 1;
			while ((str)[y] != '\n' && y > 0)
			{
				ft_putstr("\x1b[C");
				y--;
			}
			if (y == 0)
			{
				y = 11;
				while (y-- > 0)
					ft_putstr("\x1b[C");
			}
		}
	}
}

int		which_case(void)
{
	char x;

	read(0, &x, 1);
	if (x != '[')
		return (0);
	read(0, &x, 1);
	if (x == 'A')
		return (1);
	if (x == 'B')
		return (2);
	if (x == 'C')
		return (3);
	if (x == 'D')
		return (4);
	if (x == 'F')
		return (5);
	if (x == 'H')
		return (6);
	return (0);
}

char	*remalloc(char *str, char c)
{
	int		x;
	int		i;
	char	*tmp;

	x = 0;
	i = ft_strlen(str);
	tmp = ft_strdup(str);
	free(str);
	str = malloc(sizeof(char) * (i + 2));
	while (x < i)
	{
		str[x] = tmp[x];
		x++;
	}
	free(tmp);
	str[i] = c;
	str[i + 1] = '\0';
	return (str);
}

char	*strput(char *str, t_arrow *ar, char c) //multi dans multi
{
	int x;
	int y;
	int len;

	str = remalloc(str, 'X');
	len = ft_strlen(str);
	x = len + ar->x;
	y = len - 1;
	while (x <= y)
	{
		str[y] = str[y - 1];
		y--;
	}
	x = len + ar->x - 1;
	str[x] = c;
	while (x < len)
	{
		ft_putchar(str[x]);
		x++;
	}
	x = 0;
	vleft_ar(x, ar, len, str);
	return (str);
}

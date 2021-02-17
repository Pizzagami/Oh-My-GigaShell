/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bashy_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selgrabl <selgrabl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 09:59:09 by braimbau          #+#    #+#             */
/*   Updated: 2021/02/17 16:04:22 by braimbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*strdel(char *str, t_arrow *ar)
{
	int		x;
	int		len;
	char	c;

	len = ft_strlen(str);
	x = len + ar->x - 1;
	if (x + 1 < 1)
		return (str);
	c = str[x];
	while (++x < len)
	{
		str[x - 1] = str[x];
	}
	str[x - 1] = 0;
	x = len + ar->x - 2;
	vleft(c, str, x);
	while (++x < len)
	{
		ft_putchar(str[x]);
		ft_putstr(" \b");
	}
	x = len + ar->x - 1;
	while (++x < len)
		ft_putstr("\b");
	return (str);
}

void	home(char **str, t_arrow *ar, t_hist *hist)
{
	(void)hist;
	while (ft_strlen(*str) + ar->x > 0)
		wleft(ar, *str);
}

void	endl(char **str, t_arrow *ar, t_hist *hist)
{
	(void)hist;
	while (ft_strlen(*str) + ar->x < ft_strlen(*str))
		wright(ar, *str);
}

void	wleft(t_arrow *ar, char *str)
{
	int len;

	len = ft_strlen(str);
	if (str[len + ar->x] != ' ' && len + ar->x > 0)
		left(&str, ar, NULL);
	while (((str[len + ar->x] == ' ' || str[len + ar->x] == '\n')
	&& len + ar->x > 0) || ar->x == 0)
	{
		left(&str, ar, NULL);
	}
	while (str[len + ar->x] != ' ' && len + ar->x > 0)
	{
		left(&str, ar, NULL);
	}
	if (len + ar->x != 0 || (len + ar->x == 0 && str[0] == ' '))
		right(&str, ar, NULL);
}

void	wright(t_arrow *ar, char *str)
{
	int len;

	len = ft_strlen(str);
	while (str[len + ar->x] != ' ' && len + ar->x < len)
		right(&str, ar, NULL);
	while ((str[len + ar->x] == ' ' || str[len + ar->x] == '\n')
	&& len + ar->x < len)
		right(&str, ar, NULL);
}

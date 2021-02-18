/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bashy_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selgrabl <selgrabl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 09:59:09 by braimbau          #+#    #+#             */
/*   Updated: 2021/02/18 08:33:53 by braimbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	historic(t_hist *hist, char *str)
{
	int x;

	x = 254;
	if (!hist->y)
	{
		while (x >= 0)
		{
			hist->tab[x + 1] = hist->tab[x];
			x--;
		}
		hist->tab[0] = ft_strdup(str);
	}
	else
	{
		free(hist->tab[0]);
		hist->tab[0] = ft_strdup(str);
	}
}

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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bashy_tools_dir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selgrabl <selgrabl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 10:55:06 by braimbau          #+#    #+#             */
/*   Updated: 2021/02/17 15:53:53 by braimbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	mult_down(char **str, t_arrow *ar, t_hist *hist, int x)
{
	ar->y--;
	while (ar->x < 0)
	{
		ar->x++;
		ft_putstr("\033[C");
	}
	while (x > 0)
	{
		x--;
		if ((*str)[x] != '\n')
			ft_putstr("\b \b");
		else
			upanddown(str, hist, x);
	}
	if (*str)
		free(*str);
	ft_putstr(hist->tab[ar->y]);
	*str = ft_strdup(hist->tab[ar->y]);
}

void	upanddown(char **str, t_hist *hist, int x)
{
	int y;
	int i;
	int ret;

	ft_putstr("\033[A");
	y = x - 1;
	while ((*str)[y] != '\n' && y > 0)
	{
		ft_putstr("\x1b[C");
		y--;
	}
	i = y;
	ret = 0;
	while (i > 0)
	{
		if ((*str)[i] == '\n')
			ret = 1;
		i--;
	}
	if (y == 0)
	{
		y = (hist->y == 0 && ret == 0) ? 11 : 11;
		while (y-- > 0)
			ft_putstr("\x1b[C");
	}
}

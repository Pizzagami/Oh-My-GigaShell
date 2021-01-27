/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bashy_tools_dir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selgrabl <selgrabl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 10:55:06 by braimbau          #+#    #+#             */
/*   Updated: 2021/01/27 15:13:59 by selgrabl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	ft_putstr(hist->tab[ar->y]);
	*str = ft_strdup(hist->tab[ar->y]);
}

void	upanddown(char **str, t_hist *hist, int x)
{
	int y;

	ft_putstr("\033[A");
	y = x - 1;
	while ((*str)[y] != '\n' && y > 0)
	{
		ft_putstr("\x1b[C");
		y--;
	}
	if (y == 0)
	{
		y = (hist->y == 0) ? 11 : 11;
		while (y-- > 0)
			ft_putstr("\x1b[C");
	}
}

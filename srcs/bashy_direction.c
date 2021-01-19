/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bashy_direction.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braimbau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 10:55:06 by braimbau          #+#    #+#             */
/*   Updated: 2021/01/18 10:59:21 by braimbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	left(char **str, t_arrow *ar, t_hist *hist) //D
{
	int len;
	int y;

	(void)hist;
	len = ft_strlen(*str);
	if (len + ar->x > 0)
	{
		ar->x--;
		if ((*str)[len + ar->x] != '\n')
			ft_putstr("\b");
		else
		{
			ft_putstr("\033[A");
			y = len + ar->x - 1;
			while ((*str)[y] != '\n' && y > 0)
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

void	right(char **str, t_arrow *ar, t_hist *hist) //C peut etre bon
{
	int len;

	(void)hist;
	len = ft_strlen(*str);
	if (ar->x < 0)
	{
		if ((*str)[len + ar->x] != '\n')
			ft_putstr("\033[C");
		else
			ft_putstr("\n");
		ar->x++;
	}
}

void	up(char **str, t_arrow *ar, t_hist *hist) //A
{
	int x;
	int y;

	if (hist->x - 1 > ar->y || (ar->y == 0 && hist->x == 1 && !(**str)))
	{
		if (!(ar->y == 0 && !(**str)))
			ar->y++;
		x = 0;
		while (ar->x < 0)
		{
			if ((*str)[ft_strlen(*str) + ar->x] != '\n')
				ft_putstr("\033[C");
			else
				ft_putstr("\n");
			ar->x++;
		}
		x = ft_strlen(*str);
		while (x > 0)
		{
			x--;
			if ((*str)[x] != '\n')
				ft_putstr("\b \b");
			else
			{
				ft_putstr("\033[A");
				y = x - 1;
				while ((*str)[y] != '\n' && y > 0)
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
		ft_putstr(hist->tab[ar->y]);
		*str = ft_strdup(hist->tab[ar->y]);
	}
}

void	down(char **str, t_arrow *ar, t_hist *hist) //B prob hist1 ligne
{
	int x;
	int y;

	x = 0;
	while (ar->x < 0)
	{
		if ((*str)[ft_strlen(*str) + ar->x] != '\n')
			ft_putstr("\033[C");
		else
			ft_putstr("\n");
		ar->x++;
	}
	if (ar->y > 0)
	{
		ar->y--;
		x = ft_strlen(*str);
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
			{
				ft_putstr("\033[A");
				y = x - 1;
				while ((*str)[y] != '\n' && y > 0)
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
		ft_putstr(hist->tab[ar->y]);
		*str = ft_strdup(hist->tab[ar->y]);
		return ;
	}
	x = ft_strlen(*str);
	while (x > 0)
	{
		x--;
		if ((*str)[x] != '\n')
			ft_putstr("\b \b");
		else
		{
			ft_putstr("\033[A");
			y = x - 1;
			while ((*str)[y] != '\n' && y > 0)
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
	*str = ft_strdup("\0");
}


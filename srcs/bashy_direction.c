/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bashy_direction.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selgrabl <selgrabl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 10:55:06 by braimbau          #+#    #+#             */
/*   Updated: 2021/01/20 15:06:40 by selgrabl         ###   ########.fr       */
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

void	home(char **str, t_arrow *ar, t_hist *hist) //27[H 27[F end
{
	(void)hist;
	(void)str;
	(void) ar;
}

void	endl(char **str, t_arrow *ar, t_hist *hist)
{
	(void)hist;
	(void)str;
	(void) ar;
}

void	wleft(t_arrow *ar, char *str) //1
{
	int len;

	len = ft_strlen(str);
	while (ft_isalnum(str[len + ar->x]) && len + ar->x > 0)
	{
		left(&str, ar, NULL);
	}
	while (((str[len + ar->x] == ' ' || str[len + ar->x] == '\n') && len + ar->x > 0) || ar->x == 0)
	{
		left(&str, ar, NULL);
	}
	while (ft_isalnum(str[len + ar->x]) && len + ar->x > 0)
	{
		left(&str, ar, NULL);
	}
	if (len + ar->x != 0)
		right(&str, ar, NULL);
}

void	wright(t_arrow *ar, char *str) //5
{
	int len;
	char *tmp;
	//int ax;

	tmp = ft_strdup(str);
	len = ft_strlen(str);
	/*ax = ar->x;
	while (ft_isalnum(tmp[len + ax]))
		ax++;
	while (((tmp[len + ax] == ' ' || tmp[len + ax] == '\n') && len + ar->x  < len))
		ax++;
	if (ax >= 0)
	{
		free(tmp);
		return;
	} */
	while (ft_isalnum(str[len + ar->x]) && len + ar->x < len)
		right(&str, ar, NULL);
	while ((str[len + ar->x] == ' ' || str[len + ar->x] == '\n') && len + ar->x < len)
		right(&str, ar, NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bashy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braimbau <braimbau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 09:59:09 by braimbau          #+#    #+#             */
/*   Updated: 2021/01/27 12:48:47 by braimbau         ###   ########.fr       */
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

char	caspe(char c, char **str, t_arrow *ar, t_hist *hist)
{
	FLCH_CSP	*fleche_caspe[7];
	int			i;

	fleche_init(fleche_caspe);
	if (c < 1)
		return (c = '\0');
	if ((int)c == 127)
	{
		*str = strdel(*str, ar);
		c = '\0';
	}
	else if ((int)c == 1)
		wleft(ar, *str);
	else if ((int)c == 5)
		wright(ar, *str);
	else if ((int)c == 27)
	{
		i = which_case();
		(i > 0) ? (*fleche_caspe[i])(str, ar, hist) : 0;
	}
	else if (c > 31 && c < 127)
		*str = strput(*str, ar, c);
	else if (c == 9)
		auto_completion();
	return (c);
}

int		looping(char *str, char c, t_hist *hist)
{
	if ((int)c == 3)
	{
		free(str);
		ft_putchar('\n');
		hist->y = 0;
		return (3);
	}
	else
	{
		if (!hist->y)
		{
			free(str);
			str = ft_strdup("exit");
			ft_putstr("exit\n");
			historic(hist, str);
		}
		else
		{
			ft_putstr("bash: unexpected EOF while looking for matching");
			ft_putstr(" `'\"\nbash: syntaxt error: unexpected end of file");
			free(str);
		}
		return (1);
	}
}

int		loop(char *str, t_hist *hist, t_arrow *ar)
{
	char c;

	c = 0;
	while (1)
	{
		read(0, &c, 1);
		if ((int)c == 3 || ((int)c == 4 && str[0] == 0))
			return (looping(str, c, hist));
		else if ((int)c == 10)
		{
			ft_putstr("\n");
			if (str[0] != 0)
			{
				historic(hist, str);
				hist->x = (hist->x < 256 && !hist->y) ? hist->x + 1 : hist->x;
				ft_bzero(str, ft_strlen(str));
				free(str);
				return (1);
			}
			return (0);
		}
		else
			c = caspe(c, &str, ar, hist);
	}
}

int		bashy(t_hist *hist, t_arrow *ar)
{
	char *str;

	str = malloc(sizeof(char) * 1);
	str[0] = '\0';
	setcolor(&(hist->cc));
	if (hist->y)
		ft_putstr(">\033[0m");
	else
	{
		write(1, "My-Bash:", 8);
		ft_putstr("\033[0m$ ");
	}
	ar->x = 0;
	ar->y = 0;
	return (loop(str, hist, ar));
}

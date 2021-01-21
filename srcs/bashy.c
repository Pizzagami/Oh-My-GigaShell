/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bashy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selgrabl <selgrabl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 09:59:09 by braimbau          #+#    #+#             */
/*   Updated: 2021/01/21 11:32:50 by selgrabl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	historic(t_hist *hist, char *str, int y)
{
	int x;

	x = 254;
	if (!y)
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
	x = len + ar->x;
	if (x < 1)
		return (str);
	c = str[x - 1];
	while (x < len)
	{
		str[x - 1] = str[x];
		x++;
	}
	str[x - 1] = 0;
	x = len + ar->x - 1;
	vleft(c, str, x - 1);
	while (x < len)
	{
		ft_putchar(str[x]);
		ft_putstr(" \b");
		x++;
	}
	x =	len + ar->x;
	while(x < len)
	{
		ft_putstr("\b");
		x++;
	}
	return (str);
}

char	caspe(char c, char **str, t_arrow *ar, t_hist *hist)
{
	FLCH_CSP *fleche_caspe[7];

	fleche_caspe[0] = NULL;
	fleche_caspe[1] = &up;
	fleche_caspe[2] = &down;
	fleche_caspe[3] = &right;
	fleche_caspe[4] = &left;
	fleche_caspe[5] = &endl;
	fleche_caspe[6] = &home;
	if ((int)c == 9 || (int)c < 1)
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
		(*fleche_caspe[which_case()])(str, ar, hist);
	}
	else if (ft_isalnum(c) || c == ' ')
		*str = strput(*str, ar, c);
	return (c);
}

int		loop(char *str, t_hist *hist, int y, t_arrow *ar)
{
	char c;

	c = 0;
	while (1)
	{
		read(0, &c, 1);
		if ((int)c == 3) // create cas d et 
		{
			free(str);
			ft_putchar('\n');
			return (3);
		}
		else if ((int)c == 4 && str[0] == 0)
		{
			free(str);
			str = ft_strdup("exit");
			ft_putstr("exit\n");
			historic(hist, str, y);
			return(1);
		}
		else if ((int)c == 10)
		{
			ft_putstr("\n");
			if (str[0] != 0)
			{
				historic(hist, str, y);
				hist->x = (hist->x < 256 && !y) ? hist->x + 1 : hist->x;
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

int		bashy(t_hist *hist, t_arrow *ar, int y)
{
	char *str;

	str = malloc(sizeof(char) * 1);
	str[0] = '\0';
	setcolor(&(hist->cc));
	if (y)
		ft_putstr(">\033[0m");
	else
	{
		write(1, "My-Bash:", 8);
		//ft_putstr(getcwd(path, PATH_MAX - 1));
		ft_putstr("\033[0m$ ");
	}
	ar->x = 0;
	ar->y = 0;
	return(loop(str, hist, y, ar)); 
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bashy_poor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selgrabl <selgrabl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 10:23:00 by selgrabl          #+#    #+#             */
/*   Updated: 2021/02/03 14:10:23 by braimbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <termios.h>

void		fleche_init(t_flch_csp *fleche_caspe[7])
{
	fleche_caspe[0] = NULL;
	fleche_caspe[1] = &up;
	fleche_caspe[2] = &down;
	fleche_caspe[3] = &right;
	fleche_caspe[4] = &left;
	fleche_caspe[5] = &endl;
	fleche_caspe[6] = &home;
}

char		poor_caspe(char c, char **str, t_arrow *ar)
{
	int			i;
	t_flch_csp	*fleche_caspe[7];

	fleche_init(fleche_caspe);
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
		i = which_case();
		if (i > 2)
			(*fleche_caspe[i])(str, ar, NULL);
	}
	else if (c > 31 && c < 127)
		*str = strput(*str, ar, c);
	return (c);
}

int			poor_loop(char **str, t_arrow *ar, char *eof, char c)
{
	c = 0;
	while (1)
	{
		read(0, &c, 1);
		if (c == 3)
			return (3);
		else if (c == 4 && *str[0] == 0)
		{
			free(*str);
			*str = ft_strdup(eof);
			return (2);
		}
		else if (c == 10)
		{
			if (*str[0] != 0)
				return (1);
			return (0);
		}
		else
			c = poor_caspe(c, str, ar);
	}
}

int			poor_bashy(char *eof, char **str, struct termios save_cano,
struct termios save_nncano)
{
	t_arrow		ar;
	int			ret;
	char		c;

	c = 0;
	*str = malloc(sizeof(char) * 1);
	*str[0] = '\0';
	ar.y = 0;
	ar.x = 0;
	tcsetattr(0, TCSADRAIN, &save_nncano);
	ret = poor_loop(str, &ar, eof, c);
	tcsetattr(0, TCSADRAIN, &save_cano);
	if (ret != 2)
		ft_putstr("\n");
	else
		ft_putchar(' ');
	return (ret);
}

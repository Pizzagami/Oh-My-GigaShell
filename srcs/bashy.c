#include "libft.h"
#include "minishell.h"


void	historic(t_hist *hist ,char *str, int y) // enlever ligne vide et file verif taille max
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
	int x;
	int y;
	int t;

	t = 0;
	y = ft_strlen(str);
	x =	y + ar->x;
	if (x < 1)
		return(str);
	if (str[y - 1] == 9)
		t = 1;
	while (x < y)
	{
		str[x - 1] = str[x];
		x++;
	}
	if (x == y)
		{
			str[x - 1] = 0;
			y--;
		}
	x =	y + ar->x;
	while (x < y)
	{
		ft_putstr("\b");
		write(1, &(str[x]), 1);
		ft_putstr("\033[C");
		x++;
	}
	if (x == y)
		{
			ft_putstr("\b \b");
		}
	if (t == 1)
		ft_putstr("");
	x = 1;
	while (ar->x < --x)
		ft_putstr("\b");
	return (str);
}

char	*strput(char *str, t_arrow *ar, char c)
{
	int x;
	int y;

	if (ar->x == 0)
	{
		write(1, &c, 1);
		str = remalloc(str, c);
	}
	else
	{
		str = remalloc(str, 'X');
		y = ft_strlen(str);
		x =	y + ar->x;
		x++;
		while (y >= x)
		{	
			str[y - 1] = str[y - 2];
			y--;
		}
		str[y - 1] = c;
		y = ft_strlen(str);
		x = y + ar->x - 1;
		while (x <= y)
		{
			write(1, &(str[x]), 1);
			x++;
		}
		x = 1;
		while (ar->x < --x)
			ft_putstr("\b");
	}
	return (str);
}

int		which_case()
{
	char x;

	read(0, &x, 1);
	if (x != '[')
		return 0;
	read(0, &x, 1);
	if (x == 'A')
		return 1;
	if (x == 'B')
		return 2;
	if (x == 'C')
		return 3;
	if (x == 'D')
		return 4;
	return 0;
}

void	left(char **str, t_arrow *ar, t_hist *hist) //D
{
	(void)hist;
	(void)str;
	if (ft_strlen(*str) + ar->x > 0)
	{
		ar->x--;
		ft_putstr("\b");
	}		
}

void	right(char **str, t_arrow *ar, t_hist *hist) //C
{
	(void)hist;
	(void)str;
	if(ar->x < 0)
	{
		ar->x++;
		ft_putstr("\033[C");
	}
}

void	up(char **str, t_arrow *ar, t_hist *hist) //A
{
	int x;
	int y;

	if (hist->x - 1 > ar->y || (ar->y == 0 && hist->x == 1 && !(**str)))
	{
		if(!(ar->y == 0 && !(**str)))
			ar->y++;
		x = 0;
		while (ar->x < 0)
		{
			ar->x++;
			ft_putstr("\033[C");
		}
		
		x = ft_strlen(*str);
		while(x > 0)
		{
			x--;
			if ((*str)[x] != '\n')
				ft_putstr("\b \b");
			else
			{
				ft_putstr("\033[A");
			//	x--;
				y = x - 1;
				while((*str)[y] != '\n' && y > 0)
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
		ar->x++;
		ft_putstr("\033[C");
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
		while(x > 0)
		{
			x--;
			if ((*str)[x] != '\n')
				ft_putstr("\b \b");
			else
			{
				ft_putstr("\033[A");
				//x--;
				y = x - 1;
				while((*str)[y] != '\n' && y > 0)
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
		return;
	}
	x = ft_strlen(*str);
	while(x > 0)
	{
		x--;
		if ((*str)[x] != '\n')
			ft_putstr("\b \b");
		else
		{
			ft_putstr("\033[A");
			y = x - 1;
			while((*str)[y] != '\n' && y > 0)
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

char	caspe(char c, char **str, t_arrow *ar, t_hist *hist)
{
	FLCH_CSP *fleche_caspe[5];

	fleche_caspe[0] = NULL;
	fleche_caspe[1] = &up;
	fleche_caspe[2] = &down;
	fleche_caspe[3] = &right;
	fleche_caspe[4] = &left;
	if ((int)c == 9 || (int)c < 1)
		return(c = '\0');
	if((int)c == 127)
	{
	 *str = strdel(*str, ar);
		c = '\0';
	}
	else if((int)c == 27)
	{
		(*fleche_caspe[which_case()])(str, ar, hist);
	}
	else
		*str = strput(*str,ar, c);
	return(c);
}

char	*remalloc(char *str, char c)
{
	int x;
	int i;
	char *tmp;

	x = 0;
	i = ft_strlen(str);
	tmp = ft_strdup(str);
	free(str);
	str = malloc(sizeof(char) * (i + 2));
	while(x < i)
	{
		str[x] = tmp[x];
		x++;
	}
	free(tmp);
	str[i] = c;
	str[i + 1] = '\0';
	return(str);
}

int		bashy(t_hist *hist, t_arrow *ar, int y) //fleche bas casser
{
	char c;
	char *str;

	str = malloc(sizeof(char) * 1);
	str[0] = '\0';
	c ='\0';
	setcolor(&(hist->cc));
	if (y)
		ft_putstr(">\033[0m");
	else
	{
		write(1, "My-Bash:",8);
	//ft_putstr(getcwd(path, PATH_MAX - 1));
	ft_putstr("\033[0m$ ");
	}
	//279165
	while(1)
	{
		read(0, &c, 1);
		if((int)c == 3 || (int)c == 4) // create break cas
		{
			free(str);
			return(3);
		}
		else if ((int)c == 10)
		{
			ft_putstr("\n");
			ar->x = 0;
			ar->y = 0;
			if(str[0] != 0)
			{
				historic(hist, str, y);
				hist->x = (hist->x < 256 && !y) ? hist->x + 1: hist->x;
				ft_bzero(str, ft_strlen(str));
				free(str);
				return(1);
			}
			else
				return(0);
		}
		else
			c =	caspe(c, &str, ar, hist);
	}
}

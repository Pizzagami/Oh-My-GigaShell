#include "libft.h"
#include "minishell.h"


void	historic(t_hist *hist ,char *str) // enlever ligne vide et file verif taille max
{
	int x;

	x = 254;
	while (x >= 0)
	{
		hist->tab[x + 1] = hist->tab[x];
		x--;
	}
	hist->tab[0] = ft_strdup(str);
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

int which_case()
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

void right(char **str, t_arrow *ar, t_hist *hist) //D
{
	if (ft_strlen(*str) + ar->x > 0)
	{
		ar->x--;
		ft_putstr("\b");
	}		
}

void right(char **str, t_arrow *ar, t_hist *hist) //C
{
	if(ar->x < 0)
	{
		ar->x++;
		ft_putstr("\033[C");
	}
}
void up(char **str, t_arrow *ar, t_hist *hist) //A
{
	int x;

	if (hist->x > ar->y)
	{
		x = 0;
		if (ar->y == 0 && ft_strlen(*str))
			ar->y++;
		while (ar->x < 0)
		{
			ar->x++;
			ft_putstr("\033[C");
		}
		while((int)ft_strlen(*str) > x)
		{
			x++;
			ft_putstr("\b \b");
		} 
		ft_putstr(hist->tab[ar->y]);
		*str = ft_strdup(hist->tab[ar->y]);
		ar->y++;
	}
}

void down(char **str, t_arrow *ar, t_hist *hist) //B
{
	int x;
	if (ar->y > 0)
	{
		if(ar->y == hist->x)
			ar->y--;
		ar->y--;
		int x = 0;
		while (ar->x < 0)
		{
			ar->x++;
			ft_putstr("\033[C");
		}
		while((int)ft_strlen(*str) > x)
		{
			x++;
			ft_putstr("\b \b");
		}
			ft_putstr(hist->tab[ar->y]);
			*str = ft_strdup(hist->tab[ar->y]);
		return;
	}
	x = 0;
		while (ar->x < 0)
		{
			ar->x++;
			ft_putstr("\033[C");
		}
		while((int)ft_strlen(*str) > x)
		{
			x++;
			ft_putstr("\b \b");
		}
	*str = ft_strdup("\0");
}

char	caspe(char c, char **str, t_arrow *ar, t_hist *hist)	//pointeur sur fctn 
{
	char x;
	if ((int)c == 9 || (int)c < 1)
		return(c = '\0');
	if((int)c == 127)
	{
	 *str = strdel(*str, ar);
		c = '\0';
	}
	else if((int)c == 27)
	{
		*fleche_caspe[which_case](str, ar, hist);

		
		}
	}
	else
		*str = strput(*str,ar, c);
	return(c);
}

char *remalloc(char *str, char c)
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
				historic(hist, str);
				hist->x = (hist->x < 256) ? hist->x + 1: hist->x;
				ft_bzero(str, ft_strlen(str));
				free(str);
				return(1);
			}
			else
			{
				return(0);
			}
		}
		else
			c =	caspe(c, &str, ar, hist);
	}
}

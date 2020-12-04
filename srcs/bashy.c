#include "libft.h"
#include "minishell.h"


void	historic(t_hist *hist ,char *str) // enlever ligne vide et file
{
	int x;

	x = 254;
	free(hist->tab[255]);
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

char	caspe(char c, char **str, t_arrow *ar, t_hist *hist)	//pointeur sur fctn ? //fix && é etv 
{
	char x;
	if ((int)c == 9 || (int)c < 1)
		return(c = '\0');
	if((int)c == 127)
	{
	 *str = strdel(*str, ar);
		c = '\0';
	}
	else if((int)c == 27) //faire un ++ la ou l autre endroit des é
	{
		read(0, &x, 1);
		if (x == '[')
		{
			read(0, &x, 1);
		if (x == 'D' && ft_strlen(*str) + ar->x > 0)
		{
			ar->x--;
			ft_putstr("\b");
		}
		if (x == 'C')
		{
			if(ar->x < 0)
			{
				ar->x++;
				ft_putstr("\033[C");
			}
		}
		if (x == 'A' && hist->x > ar->y) // separer pour normer
		{
			int x = 0;
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
		if (x == 'B' && ar->y > 0)
		{
			if(ar->y == hist->x)
				ar->y--;
			ar->y --;
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
			if (ar->y == 0)
			{
				*str = ft_strdup("\0");
			}
			else
			{
				ft_putstr(hist->tab[ar->y]);
				*str = ft_strdup(hist->tab[ar->y]);
			}
		}
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

int		bashy(t_hist *hist, t_arrow *ar)
{
	char c;
	char *str;

	str = malloc(sizeof(char) * 1);
	str[0] = '\0';
	c ='\0';
	setcolor(&(hist->cc));
	write(1, "My-Bash:",8);
	ft_putstr("\033[0m");
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
			}
			else
			{
				if (bashy(hist, ar) == 3)
				return(3);
			}
			return(0);
		}
		else
			c =	caspe(c, &str, ar, hist);
	}
}

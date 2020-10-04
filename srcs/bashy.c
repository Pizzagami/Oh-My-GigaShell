#include "libft.h"
#include "minishell.h"


void	historic(t_hist *hist ,char *str)
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

	y = ft_strlen(str);
	x =	y + ar->x;
	if (x < 1)
		return(str);
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


char	caspe(char c, char **str, t_arrow *ar, t_hist *hist)	//pointeur sur fctn ?	
{

	char x[3];
	if((int)c == 127)
	{
	 *str = strdel(*str, ar); //traitemnt string del
		c = '\0';
	}
	else if((int)c == 27)
	{
		read(0,x,2);
		x[2] = '\0';
		if (ft_strcmp("[C",x) == 0 && ft_strlen(*str) + ar->x > 0)
		{
			ar->x--;
			ft_putstr("\b");
		}
		else if (ft_strcmp("[D",x) == 0)
		{
			if(ar->x < 0)
			{
				ar->x++;
				ft_putstr("\033[C");
			}
		}
		else if (ft_strcmp("[B",x) == 0 && hist->x > ar->y) // separer pour normer
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
		else if (ft_strcmp("[A",x) == 0 && ar->y > 0)
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
			ft_putstr(hist->tab[ar->y]);
			*str = ft_strdup(hist->tab[ar->y]);
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
	write(1, "My-Bash $ ",10);
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
			historic(hist, str);
			hist->x++;
			ft_bzero(str, ft_strlen(str));
			return(0);
		}
		else
			c =	caspe(c, &str, ar, hist);
	}
}

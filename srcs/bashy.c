#include "libft.h"
#include "minishell.h"


void 	parse(t_hist *hist ,char *str)
{
	if(hist->x < 256)
	{
		hist->tab[hist->x] = str;
		hist->x++;
	}
}

void	strdel(char **str, t_arrow *ar)
{
	int x;

	x = ft_strlen(*str) + ar->x;
	while (x + 1 < (int)ft_strlen(*str))
	{
		
		*(str[x]) = (x + 1 == (int)ft_strlen(*str)) ? 0: *(str[x + 1]);
		write(1, &(*str[x]), 1);
		x++;
	}
	x = 0;
	while (x > ar->x)
	{
		ft_putstr("\b");
		x--;
	}
	str[x] = 0;
}


char	caspe(char c, char **str, t_arrow *ar)	//pointeur sur fctn ?	
{

	char x[3];
	if((int)c == 127)
	{
		strdel(str, ar); //traitemnt string del
		c = '\0';
	}
	else if((int)c == 27)
	{
		read(0,x,2);
		x[2] = '\0';
		if (ft_strcmp("[D",x) == 0)
		{
			ar->x--;
			ft_putstr("\b");
		}
		if (ft_strcmp("[C",x) == 0)
		{
			if(ar->x < 0)
			{
				ar->x++;
				ft_putstr("\033[C");
			}
		}
		if (ft_strcmp("[A",x) == 0)
			ar->y--;
		if (ft_strcmp("[B",x) == 0)
			ar->y++;
	}
	else
	{
		*str = remalloc(*str, c);
		write(1, &c, 1);
	}
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
	write(1, "&>",2);
	while(1)
	{
		read(0, &c, 1);
		if((int)c == 3 || (int)c == 4) // create break cas
			break;
		else if ((int)c == 10)
		{
			ft_putstr("\r\n&>");
			parse(hist, str);
			ft_bzero(str, ft_strlen(str));
		}
		else
			c =	caspe(c, &str, ar);
	}
	free(str);
	return(0);
}

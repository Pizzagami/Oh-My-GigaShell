#include "libft.h"
#include "minishell.h"


void 	parse(t_hist *hist ,char *str)
{
	if(hist->x < 256)
	{
		hist->tab[hist->x] = str;
		hist->x++;
	}
	putstr("parsing....\n\r");
}

char caspe(char c)	//pointeur sur fctn ?	
{
	if((int)c == 127)		//bloquer le del &>
	{
		putstr("\b \b");
		c = '\0';
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
	tmp = str;
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

int		bashy(t_hist *hist)
{
	char c;
	char *str;

	str = malloc(sizeof(char) * 1);
	str[0] = '\0';
	c ='\0';
	write(1, "&>",2);
	while(1)
	{
		write(1, &c, 1);
		read(fd, &c, 1);
		if((int)c == 3 || (int)c == 4) // create break cas
			break;
		else if ((int)c == 10)
		{
			putstr("\r\n&>");
			parse(hist, str);
			ft_bzero(str, ft_strlen(str));
			c = '\0';
		}
		else
			str = remalloc(str);
	}
	free(str);
}

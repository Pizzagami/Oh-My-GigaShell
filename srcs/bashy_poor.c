#include "minishell.h"
#include <termios.h>

char	poor_caspe(char c, char **str, t_arrow *ar)
{
	FLCH_CSP *fleche_caspe[7];

	fleche_caspe[0] = NULL;
	fleche_caspe[1] = NULL;
	fleche_caspe[2] = NULL;
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
		(*fleche_caspe[which_case()])(str, ar, NULL);
	}
	else if (c > 31 && c < 127)
		*str = strput(*str, ar, c);
	return (c);
}

int     poor_loop(char **str, t_arrow *ar,char *eof)
{
	char c;

	c = 0;
	while (1)
	{
		read(0, &c, 1);
		ft_putnbr(c);
		if ((int)c == 3)
		{
			free(*str);
			return (3);
		}
		else if ((int)c == 4 && *str[0] == 0)
		{
            free(*str);
            *str = ft_strdup(eof);
			return(2);
		}
		else if ((int)c == 10)
		{

			if (*str[0] != 0)
			{
				ft_bzero(*str, ft_strlen(*str));
				return (1);
			}
			return (0);
		}
		else
			c = poor_caspe(c, str, ar);
	}
}

int     poor_bashy(char *eof,char **str)
{
    struct termios save_cano;
	struct termios config;
    t_arrow ar;
    int ret;

	*str = malloc(sizeof(char) * 1);
	*str[0] = '\0';
    tcgetattr(0, &save_cano);
    config.c_lflag &= ~(ECHO | ICANON | ISIG);
	 tcsetattr(0, TCSADRAIN, &config);
	ar.y = 0;
	ar.x = 0;
    ret = poor_loop(str,&ar, eof);
    tcsetattr(0, TCSADRAIN, &save_cano);
	ft_putstr("\n");
    return(ret);
}
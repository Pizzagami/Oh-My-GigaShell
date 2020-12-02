#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include "libft.h"

void    buitin_echo(char **str)
{
    int n;
    int x;

    x = 0;
    n = 0;
    if (ft_strcmp(*str, "-n") == 0)
    {
        n = 1;
        str++;
    }
    while (str && *str)
    {
        if (x > 0)
            ft_putstr(" ");
        ft_putstr(*str);
        str++;
        x++;
    }
   /* if (n == 1)
    {
        if (*(str[ft_strlen(*str) - 1]) != '\n')
            {
                write(1,"%",1);//changer couleur fond
            }
    } */
    if (n == 0)
    {
        write(1,"\n",1);
    }
}
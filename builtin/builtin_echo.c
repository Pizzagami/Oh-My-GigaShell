#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include "libft.h"

void    buitin_echo(char **str, int n)
{
    while (*str)
    {
        ft_strlen(*str);
        ft_putstr(*str); //verifier /n
        ft_putstr(" ");
        *str++;
    }
    if (n == 1)
    {
        if (*(str[ft_strlen(*str) - 1]) != '/n')
            {
                write(1,"%",1);
            }
    } 
}
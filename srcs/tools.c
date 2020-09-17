#include "minishell.h"
#include <stdlib.h>

void ft_init_tab(t_hist *hist)
{
    int x;

    x = 0;
    while(x < 256)
    {
        hist->tab[x] = malloc(sizeof(char));
        hist->tab[x][0] = 0;
        x++;
    }
}
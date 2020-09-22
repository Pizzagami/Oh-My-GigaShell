#include "minishell.h"
#include <stdlib.h>
#include "parser.h"

void	printf_token(t_token *token_o)
{
	int		i;
	t_token *token;

	token = token_o;
	i = 0;
	while (token)
	{
		printf("token nᵒ %d : _%s_ type = %d\n\r", i, token->str, token->type);
		i++;
		token = token->next;
	}
}

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
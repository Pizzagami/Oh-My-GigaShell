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
		printf("token nᵒ %d : _%s_ type = %d\n", i, token->str, token->type);
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

char *replace_occurence(char *str, char *to_rep, char *rep_by)
{
	int i;
	char *tmp;
	char *ret;

	ret = NULL;
	i = ft_findstr(str, to_rep);
	ret = ft_substr(str, 0, i);
	tmp = ret;
	ret = ft_strjoin(ret, rep_by);
	free(tmp);
	tmp = ret;
	ret = ft_strjoin(ret, str + i + ft_strlen(to_rep));
	free(tmp);
	return (ret);
}

char *replace_occurences(char *str, char *to_rep, char *rep_by)
{
	char *tmp;
	
	tmp = NULL;
	while(ft_findstr(str, to_rep) != -1)
	{
		str = replace_occurence(str, to_rep, rep_by);
		if (tmp)
			free(tmp);
		tmp = str;
	}
	return (str);
}

void replace_dolint(t_token *a, int ret)
{
	char *tmp;

	while (a && (a->type < SEMI || a->type > PIPE))
	{
		if (ft_findstr(a->str, "$?") != -1)
		{
			tmp = a->str;
			a->str = replace_occurences(a->str, "$?", ft_itoa(ret));
			free(tmp);
		}
		a = a->next;
	}
}

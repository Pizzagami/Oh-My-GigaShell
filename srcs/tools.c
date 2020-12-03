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

void replace_dollar(t_token *a, t_omm omm)
{
	char *tmp;
	char *key;
	char index;
	char *value;
	char *subkey;

	while (a && (a->type < SEMI || a->type > PIPE))
	{
		index = ft_strfind(a->str, CDOLLAR);
		while (index != -1)
		{
			key = ft_substr(a->str, index, ft_strfind(a->str, CDOLLEND) - index + 1);
			subkey = ft_substr(key, 1, ft_strlen(key) - 2);
			value = NULL;
			tmp = a->str;
			if (key[1] == '?' && ft_strlen(key) == 3)
				value = ft_itoa(*(omm.last_ret));
			else if (get_env(omm.env, subkey))
				value = ft_strdup(get_env(omm.env, subkey));
			a->str = replace_occurence(a->str, key, value); 
			index = ft_strfind(a->str, CDOLLAR);
			free(tmp);
			free(key);
			free(subkey);
			if (value)
				free(value);
		}

		a = a->next;
	}
}

char *str_up(char *s)
{
	int i;

	i = 0;
	while (s && s[i])
	{
		if (s[i] >= 'a' && s[i] <= 'z')
			s[i] -= 32;
		i++;
	}
	return (s);
}

char *str_low(char *s)
{
	int i;

	i = 0;
	while (s && s[i])
	{
		if (s[i] >= 'A' && s[i] <= 'Z')
			s[i] += 32;
		i++;
	}
	return (s);
}

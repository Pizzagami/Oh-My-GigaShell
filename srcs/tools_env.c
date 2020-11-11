#include <stdlib.h>
#include "minishell.h"

void	env_split(char *str, char **name, char **val)
{
	int i;
	int j;
	int x;
	char *str1;
	char *str2;

	i = 0;
	j = 0;
	x = 0;
	while(str && str[i] != '=')
		i++;
	str1 = malloc(sizeof(char) * i);
	str1[i - 1] = 0;
	while(j < i)
	{
		str1[j] = str[j];
		j++;
	}
	i++;
	j++;
	while(str[i])
		i++;
	str2 = malloc(sizeof(char) * (i - j));
	str2[i - j - 1] = 0;
	while(j < i)
	{
		str2[x] = str[j];
		x++;
		j++;
	}
	*name = str1;
	*val = str2;
}

int		find_and_replace(t_env **first, char *var)
{
	t_env *current;
	int  i;
	int	l_var;
	int l_name; //mettre dans la struct pour gagner des lignes?

	i = 1;
	l_var = ft_strlen(var);
	l_name = ft_strlen(current->name);
	current = *first;
	while (current)
	{
		if (!ft_strncmp(current->name, var, l_name) && var[l_name] == '=')
			{
				free(current->val);
				current->val = malloc(sizeof(char)* (l_var - l_name));
				current->val[l_var - l_name] = 0;
				while(l_name + i < l_var)
				{
					current->val[i - 1] = var[l_name + i];
					i++;
				}
				return(1);
			}
		current = current->next;
	}
	return (0);
}
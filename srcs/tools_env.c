#include <stdlib.h>
#include "minishell.h"
#include "libft.h"

int		env_split(char *str, char **name, char **val) //passer en int pour verif cas d erreur
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
	{
		if (((str[i] > 47 && str[i] < 58) && i > 0) || (str[i] > 96 && str[i] < 123)
		||(str[i] > 64 && str[i] < 91) || str[i] == '_')
		i++;
		else
			return (-1);
	}
	str1 = malloc(sizeof(char) * (i + 1));
	str1[i] = 0;
	while(j < i)
	{
		str1[j] = str[j];
		j++;
	}
	i++;
	j++;
	while(str[i])
		i++;
	str2 = malloc(sizeof(char) * (i - j + 1));
	str2[i - j] = 0;
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
	i = 1;
	current = *first;
	l_var = ft_strlen(var);
	current = *first;
	while (current)
	{
		if (!ft_strncmp(current->name, var, current->l_name) && var[current->l_name] == '=')
			{
				if (current->val)
					free(current->val);
				current->val = malloc(sizeof(char)* (l_var - current->l_name));
				current->val[l_var - current->l_name] = 0;
				while(current->l_name + i < l_var)
				{
					current->val[i - 1] = var[current->l_name + i];
					i++;
				}
				return(1);
			}
		current = current->next;
	}
	return (0);
}

void	swap_list(t_env **tmp)
{
	char *n;
	char *v;
	int	 l;

	n = (*tmp)->name;
	v = (*tmp)->val;
	l = (*tmp)->l_name;
	(*tmp)->name = (*tmp)->next->name;
	(*tmp)->val = (*tmp)->next->val;
	(*tmp)->l_name = (*tmp)->next->l_name;
	(*tmp)->next->name = n;
	(*tmp)->next->val = v;
	(*tmp)->next->l_name = l;
}

t_env	*cpy_env(t_env *env)
{
	t_env *first;
	t_env *cpy;
	t_env *next;

	first = NULL;
	while(env)
	{
		cpy = malloc(sizeof(t_env));
		cpy->name = dup(env->name);
		cpy->val = dup(env->val);
		cpy->next = dup(env->next);
		cpy->l_name = env->l_name;
		if (!first)
			first = cpy;
		if (!env->next)
			break;
		env = env->next;
		cpy = cpy->next;
	}
	return(first);
}

void 	tri_and_print(t_env *first)
{
	t_env *tmp;
	int i;
	int y;

	i = 0;
	tmp = cpy_env(first);
	while (tmp->next)
	{
		y = (tmp->l_name > tmp->next->l_name) ? tmp->l_name : tmp->next->l_name;
		if (ft_strncmp(tmp->name, tmp->next->name,y) < 0)
		{
			swap_list(&tmp);
			tmp = first;
			i = 0;
		}
		else
		{
			tmp = tmp->next;
			i++;
		}
	}
	while (tmp->next)
	{
		ft_putstr("declare -x ");
		ft_putstr(tmp->name);
		if(tmp->val)
		{
			ft_putstr("=\"");
			ft_putstr(tmp->val);
			ft_putstr("\"");
		}
		tmp = tmp->next;
	}
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selgrabl <selgrabl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 11:29:21 by braimbau          #+#    #+#             */
/*   Updated: 2021/01/08 14:42:42 by selgrabl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"
#include "libft.h"

int		env_split(char *str, char **name, char **val)
{
	int		i;
	int		j;
	int		x;
	int		ret;
	char	*str1;
	char	*str2;

	i = 0;
	j = 0;
	x = 0;
	ret = 0;
	str2 = NULL;
	while (str && str[i] != '=')
	{
		if (((str[i] > 47 && str[i] < 58) && i > 0) || (str[i] > 96 && str[i] < 123)
		|| (str[i] > 64 && str[i] < 91) || str[i] == '_')
			i++;
		else if (!str[i])
		{
			ret = 2;
			break ;
		}
		else
			return (-1);
	}
	str1 = malloc(sizeof(char) * (i + 1));
	str1[i] = 0;
	while (j < i)
	{
		str1[j] = str[j];
		j++;
	}
	if (ret != 2)
	{
		i++;
		j++;
		while (str[i])
			i++;
		str2 = malloc(sizeof(char) * (i - j + 1));
		str2[i - j] = 0;
		while (j < i)
		{
			str2[x] = str[j];
			x++;
			j++;
		}
	}
	*name = str1;
	*val = str2;
	return (ret);
}

int		find_and_replace(t_env **first, char *var)
{
	t_env	*current;
	int		i;
	int		l_var;

	i = 1;
	current = *first;
	l_var = ft_strlen(var);
	current = *first;
	while (current)
	{
		printf("%s %d\n", current->name, current->l_name);
		if (ft_strncmp(current->name, var, current->l_name) == 0
		&& (var[current->l_name] == '=' || var[current->l_name] == 0))
		{
			if (current->val)
				free(current->val);
			current->val = ft_substr(var, current->l_name + 1, l_var - current->l_name - 1);
			return (1);
		}
		current = current->next;
		//ft_putstr("1\n");
	}
	return (0);
}

void	swap_list(t_env **tmp)
{
	char	*n;
	char	*v;
	int		l;

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
	t_env *cpy;

	if (!env)
		return (NULL);
//	ft_putstr("yep:");
	cpy = malloc(sizeof(t_env));
	cpy->name = ft_strdup(env->name);
	if (env->val)
		cpy->val = ft_strdup(env->val);
	else
		cpy->val = NULL;
	cpy->l_name = env->l_name;
	//ft_putstr(cpy->name);
	//ft_putstr("\n");
	cpy->next = cpy_env(env->next);
	return (cpy);
}

void		tri_and_print(t_env *first)
{
	t_env *tmp;
	t_env *fre;
	t_env *start;

	start = cpy_env(first);
	tmp = start;
	while (tmp->next)
	{
		if (ft_strcmp(tmp->name, tmp->next->name) > 0)
		{
			swap_list(&tmp);
			tmp = start;
		}
		else
			tmp = tmp->next;
	}
	tmp = start;
	while (tmp)
	{
		ft_putstr("declare -x ");
		ft_putstr(tmp->name);
		free(tmp->name);
		if (tmp->val)
		{
			ft_putstr("=\"");
			ft_putstr(tmp->val);
			free(tmp->val);
			ft_putstr("\"\n");
		}
		else
			ft_putstr("=''\n");
		fre = tmp;
		tmp = tmp->next;
		free(fre);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selgrabl <selgrabl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 11:29:21 by braimbau          #+#    #+#             */
/*   Updated: 2021/01/27 14:38:12 by selgrabl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"
#include "libft.h"

int		find_and_replace(t_env **first, char *var)
{
	t_env	*current;
	int		l_var;

	current = *first;
	l_var = ft_strlen(var);
	current = *first;
	while (current)
	{
		if (ft_strncmp(current->name, var, current->l_name) == 0
		&& (var[current->l_name] == '=' || var[current->l_name] == 0))
		{
			if (current->val)
				free(current->val);
			current->val = ft_substr(var, current->l_name + 1,
					l_var - current->l_name - 1);
			return (1);
		}
		current = current->next;
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
	cpy = malloc(sizeof(t_env));
	cpy->name = ft_strdup(env->name);
	if (env->val)
		cpy->val = ft_strdup(env->val);
	else
		cpy->val = NULL;
	cpy->l_name = env->l_name;
	cpy->next = cpy_env(env->next);
	return (cpy);
}

void	printex(t_env *tmp)
{
	t_env *fre;

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

void	triex(t_env *first)
{
	t_env *tmp;
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
	printex(tmp);
}

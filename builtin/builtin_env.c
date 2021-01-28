/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selgrabl <selgrabl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 10:23:00 by selgrabl          #+#    #+#             */
/*   Updated: 2021/01/28 11:08:50 by selgrabl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

void	builtin_env(t_env *first)
{
	t_env *current;

	current = first;
	while (current && current->name && current->val)
	{
		ft_putstr(current->name);
		ft_putstr("=");
		ft_putstr(current->val);
		write(1, "\n", 1);
		current = current->next;
	}
}

t_env	*export(t_env *current, char *val, char *name)
{
	while (current->next)
		current = current->next;
	current->next = malloc(sizeof(t_env));
	if (current->next == NULL)
		exit(0);
	current = current->next;
	current->name = name;
	current->l_name = ft_strlen(name);
	current->val = val;
	current->next = NULL;
	return (current);
}

void	builtin_export(char **var, t_env **first)
{
	t_env	*current;
	char	*val;
	char	*name;

	current = *first;
	if (*var == NULL)
		triex(current);
	while (*var)
	{
		if (find_and_replace(first, *var) != 1)
		{
			if (env_split(*var, &name, &val) < 0)
			{
				ft_putstr("bash: export: `");
				ft_putstr(*var);
				ft_putstr("': not a valid identifier\n");
				return ;
			}
			current = export(current, val, name);
		}
		var++;
	}
}

t_env	*unset(t_env *current, t_env *tmp, char **var, int *i)
{
	if (!ft_strcmp(current->next->name, *var))
	{
		if ((int)ft_strlen(*var) == current->next->l_name)
		{
			free(current->next->name);
			free(current->next->val);
			tmp = current->next;
			current->next = current->next->next;
			free(tmp);
			*i = 1;
			return (current);
		}
		else if (*var[current->next->l_name] == '=')
		{
			ft_putstr("bash: unset: `");
			ft_putstr(*var);
			ft_putstr("': not a valid identifier\n");
		}
	}
	current = current->next;
	*i = 0;
	return (current);
}

void	builtin_unset(char **var, t_env **env)
{
	t_env	*current;
	t_env	*tmp;
	int		i;

	i = 0;
	tmp = NULL;
	current = *env;
	while (*var)
	{
		while (current->next != NULL)
		{
			current = unset(current, tmp, var, &i);
			if (i == 1)
				break ;
		}
		var++;
	}
}

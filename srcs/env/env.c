/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selgrabl <selgrabl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 15:59:42 by braimbau          #+#    #+#             */
/*   Updated: 2021/01/27 15:17:39 by selgrabl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <pwd.h>

void	dup_env(char **envp, t_env **env)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		add_tail(ft_strdup(envp[i]), env);
		i++;
	}
}

void	add_tail(char *var, t_env **first)
{
	t_env	*current;
	t_env	*next;
	char	*name;
	char	*val;

	current = *first;
	env_split(var, &name, &val);
	free(var);
	if (!val)
		return (ft_putstr("error parsing env\n"));
	if ((next = (t_env *)malloc(sizeof(t_env))) == NULL)
		exit(0);
	next->name = name;
	next->val = val;
	next->l_name = ft_strlen(name);
	next->next = NULL;
	if (current == NULL)
		*first = next;
	else
	{
		while (current->next != NULL)
			current = current->next;
		current->next = next;
	}
}

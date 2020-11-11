#include "libft.h"
#include "minishell.h"

void	built_in_env(t_env *first)
{
	t_env *current;

	current = first;
	while(current && current->name && current->val &&
	ft_strcmp(current->name,"_") && ft_strncmp(current->val,"/usr/bin/",9))
	{
		if ()
		ft_putstr(current->name);
		ft_putstr("=");
		ft_putstr(current->val);
		current = current->next;
	}
	current = first;
	while(current && current->name && current->val &&
	!ft_strcmp(current->name,"_") && !ft_strncmp(current->val,"/usr/bin/",9))
	{
		ft_putstr(current->name);
		ft_putstr("=");
		ft_putstr(current->val);
		current = current->next;
	}
}

void	built_in_export(char *var, t_env **first)
{
	if (var == NULL)
		tri_and_print(first); //tri et affiche
	else if(!find_and_replace(first, var)) //creer si pas deja existant
	{
		//env split avec verif et cas de null ou NULL et caractere interdit
	}
	free(var);
}

void	built_in_unset(char *var, t_env *lst)
{
	t_env *tmp = lst;

	if (var == NULL)
	{
		ft_putstr("unset: not enough arguments\n");
		return;
	}
	while(lst->next != NULL)
	{
		if (tmp->var && ft_strncmp(lst->next->var, var, ft_strlen(var)) == 0)
		{
			ft_putstr("var\n");
			tmp = lst->next;
			free(tmp->var);
			free(tmp);
			lst->next = lst->next->next;
		}
		else if (tmp->cache && ft_strncmp(lst->next->var, var, ft_strlen(var)) == 0)
		{
			ft_putstr("cache\n");
			tmp = lst->next;
			free(tmp->cache);
			free(tmp);
			lst->next = lst->next->next;
		}
		if (lst->next != NULL)
			lst = lst->next;
	}
}
#include "libft.h"
#include "minishell.h"

void	built_in_env(t_env *first)
{
	t_env *current;

	current = first;
	while(current && current->name && current->val &&
	ft_strcmp(current->name,"_") && ft_strncmp(current->val,"/usr/bin/",9))
	{
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
	t_env	*current = *first;
	t_env	*next = NULL;
	char *val;
	char *name;

	if (var == NULL)
		tri_and_print(*first); //tri et affiche
	else if(!find_and_replace(first, var)) //creer si pas deja existant
	{
		env_split(var, &name, &val); //faut verif
		while (current->next)
			current = current->next;
		current->next = malloc(sizeof(t_env));
		if (next == NULL)
			exit(0);
		current = current->next;
		current->name = name;
		current->val = val;
		//env split avec verif et cas de null ou NULL et caractere interdit
	}
	free(var);
}

void	built_in_unset(char *var, t_env **env)
{
	t_env *current;
	t_env *tmp;
	
	current = *env;
	while(current->next != NULL)
	{
		if (!ft_strncmp(current->next->name, var, current->next->l_name) && var[current->next->l_name] == '=')
		{
			free(current->next->name);
			free(current->next->val);
			free(current->next->l_name);
			tmp = current->next;
			current->next = current->next->next;
			free(tmp);  //aucune idee de si ca marche
			break;
		}
		current = current->next;		
	}
}
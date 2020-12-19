#include "libft.h"
#include "minishell.h"

void	builtin_env(t_env *first)
{
	t_env *current;

	current = first;
	while(current && current->name && current->val)
	{
		if (ft_strcmp(current->name,"_"))// && ft_strncmp(current->val,"/usr/bin/",9))
		{
			ft_putstr(current->name);
			ft_putstr("=");
			ft_putstr(current->val);
			write(1,"\n",1);
		}
		current = current->next;
	}
	current = first;
	while(current && current->name && current->val)
	{
		if (!ft_strcmp(current->name,"_"))// && !ft_strncmp(current->val,"/usr/bin/",9))
		{
			ft_putstr(current->name);
			ft_putstr("=");
			ft_putstr(current->val); //prendre la derniere string sorti en entree
			write(1,"\n",1); //mettre bon path de base a la main dans env
		}
		current = current->next;
	}
}

void	builtin_export(char **var, t_env **first) //gerer multi val
{
	t_env	*current = *first;
	char *val;
	char *name;

	if (*var == NULL)
		tri_and_print(current); //tri et affiche
	while (*var)
	{
		if(!find_and_replace(first, *var)) //creer si pas deja existant
		{
			ft_putstr("2\n");
			env_split(*var, &name, &val); //faut verif
			ft_putstr("3\n");
			while (current->next)
				current = current->next;
			current->next = malloc(sizeof(t_env));
			if (current->next == NULL)
				exit (0);
			current = current->next;
			current->name = name;
			current->val = val;
			//env split avec verif et cas de null ou NULL et caractere interdit
		}
		ft_putstr("4\n");
		//free(*var);
		var++;
	}
}

void	builtin_unset(char *var, t_env **env) //gerer multi val
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
			tmp = current->next;
			current->next = current->next->next;
			free(tmp);  //aucune idee de si ca marche
			break;
		}
		current = current->next;		
	}
}
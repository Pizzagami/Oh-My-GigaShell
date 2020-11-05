#include "libft.h"
#include "minishell.h"

void	built_in_env(t_env *first)
{
	t_env	*tmp = first;
	while (tmp)
	{
		if (tmp->var && ft_strncmp(tmp->var, "_=/usr/bin/", 10))
		ft_putstr(tmp->var);
		write(1, '\n');
		tmp = tmp->next;
	}
	tmp = first;
	while (tmp)
	{
		if (tmp->var && !ft_strncmp(tmp->var, "_=/usr/bin/", 10))
		ft_putstr(tmp->var);
		write(1, '\n');
		tmp = tmp->next;
	}

}

void	built_in_export(char *var, t_env **first)
{
	if (var == NULL)
		ft_trilst(&*first);
	else if(ft_strlst(&*first, ft_strdup(var)) == 1)
		ft_replace(&*first, ft_strdup(var));
	else
	{
		if (ft_strrchr(var, '=') == NULL)
			add_cache(ft_strdup(var), &*first);
		else
			add_tail(ft_strdup(var), &*first);
	}
	free(var);
}

/*void	built_in_unset(char *var, t_env *lst)
{
	t_env *tmp = lst;
	char *nop;
	int i;

	i = 0;
	nop = "=\%\\/§!-";
	if (var == NULL)
	{
		ft_putstr("unset: not enough arguments\n");
		return;
	}
	while (nop[i])
	{
		if (strchr(var, nop[i]))
		{
			ft_putstr("unset: ");
			ft_putstr(var);
			ft_putstr(": invalic parameter name\n");
			return;
		}
		i++;
	}
	while(lst->next != NULL)
	{
		if (tmp->var && ft_strcmp(lst->next->var, var) == 61)
		{
			ft_putstr("var\n");
			tmp = lst->next;
			free(tmp->var);
			free(tmp);
			lst->next = lst->next->next;
		}
		if (lst->next != NULL)
			lst = lst->next;
	}
}
*/
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
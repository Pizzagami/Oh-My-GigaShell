#include "minishell.h"
#include "libft.h"
#include <pwd.h>

void	dup_env(char **envp, t_env **env)
{
	int		i = 0;
	while (envp[i])
	{
		add_tail(ft_strdup(envp[i]), env);
		i++;
	}
}

void	add_tail(char *var, t_env **first)
{
	t_env	*current = *first;
	t_env	*next = NULL;
	char 	*name;
	char 	*val;
	env_split(var, &name, &val);
	free(var);
	if (!val)
	{
		ft_putstr("error parsing env\n");
		return;
	}
	next = (t_env *)malloc(sizeof(t_env));
	if (next == NULL)
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

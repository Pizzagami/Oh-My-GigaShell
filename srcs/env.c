#include "minishell.h"
#include "libft.h"
#include <pwd.h>

void	dup_env(char **envp, t_env **env)
{
//	char	*var_lst[] = {"PATH", "HOME", "OLDPWD", "PWD", "SHLVL", NULL};
//	int		nb_elem = 5;
	int		i = 0;
	while (envp[i])
	{
		add_tail(ft_strdup(envp[i]), env);
	/*	if (!ft_strncmp(envp[i], "PATH", 4))
			var_lst[0] = NULL;
		else if (!ft_strncmp(envp[i], "HOME", 4))
			var_lst[1] = NULL;
		else if (!ft_strncmp(envp[i], "OLDPWD", 6))
			var_lst[2] = NULL;
		else if (!ft_strncmp(envp[i], "PWD", 3))
			var_lst[3] = NULL;
		else if (!ft_strncmp(envp[i], "SHLVL", 5))
			var_lst[4] = NULL;
	*/	i++;
	}
/*	i = 0;
	while (i < nb_elem)
	{
		if (var_lst[i] != NULL)
			add_env_var(var_lst[i], &*env);
		i++;
	}
*/}

void	add_tail(char *var, t_env **first)
{
	t_env	*current = *first;
	t_env	*next = NULL;
	char 	*name;
	char 	*val;
	env_split(var, &name, &val);
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

#include "minishell.h"
#include "parser.h"

void	builtin_cd(char *path, t_env *env)
{
	char	htap[PATH_MAX];
	char	**oldpwd;
	char	**pwd;

	if (!path || !ft_strcmp(path, "~"))
		path = *get_env2(env,"HOME");
	if (chdir(path) == 0)
	{
		pwd = get_env2(env,"PWD");;
		oldpwd = get_env2(env,"OLDPWD");
		if (!oldpwd && !pwd)
			{
				free(oldpwd);
				oldpwd = pwd;
				*pwd = getcwd(htap, PATH_MAX - 1);
			}
	}
	else
	{
		ft_putstr("bash: cd: ");
		perror(path);
	}
}

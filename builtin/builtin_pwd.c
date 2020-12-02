#include "minishell.h"
#include "limits.h"
 
 void		builtin_pwd(void)
{
	char	path[PATH_MAX];
		ft_putstr(getcwd(path, PATH_MAX - 1));
	return;
}

#include "minishell.h"
#include "parser.h"
#include "libft.h"

int is_unicorn_set(t_env *env)
{
	char *str = get_env(env, "unicorn");
	if (str == NULL)
		return (-1);
	if (ft_strcmp(str, "1"))
		return (-1);
	else
		return (0);
}

void setcolor (int *x)
{
	if (*x == 0)
		ft_putstr("\033[1;34m");
	if (*x == 1 || *x == -1)
		ft_putstr("\033[1;36m");
	if (*x == 2)
		ft_putstr("\033[1;32m");
	if (*x == 3)
		ft_putstr("\033[1;33m");
	if (*x == 4)
		ft_putstr("\033[1;31m");
	if (*x == 5)
	{
		ft_putstr("\033[1;35m");
		*x = 0;
	}
	else if (*x != -1)
		(*x)++;

}

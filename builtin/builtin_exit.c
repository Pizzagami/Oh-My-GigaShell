#include "minishell.h"

void    builtin_exit(t_env *env)
{
    free_env(env);
    exit(0);
}
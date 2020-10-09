#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
 
#define PATH_MAX        1024 //faire .h
 
void		builtin_pwd(void)
{
	char	path[PATH_MAX];
		ft_putstr(getcwd(path, PATH_MAX - 1));
	return;
}

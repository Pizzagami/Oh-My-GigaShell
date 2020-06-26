#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
 
#define PATH_MAX        1024
 
void		builtin_pwd(void)
{
	char	buff[PATH_MAX];
	(void)argv; 
	if (argc == 1)
		printf("pwd: %s\n", getcwd(buff, PATH_MAX -1));
	
	return;
}

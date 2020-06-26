#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
 
#define PATH_MAX        1024
 
int		main(int argc, char *argv[])
{
	int	ret;
	char	buff[PATH_MAX];
 
	if (argc > 1)
	{
		printf("before: %s\n", getcwd(buff, PATH_MAX -1));
		ret = chdir(argv[1]);
		printf("after: %s\n", getcwd(buff, PATH_MAX -1));
	}
	
	return (ret);
}

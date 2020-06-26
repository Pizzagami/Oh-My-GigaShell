#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

void	built_in_cd(char *path)
{
	if (chdir(path) == -1)
	{
		perror("chdir()");
	}
}

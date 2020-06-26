#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "libft.h"

void	launch_builtin(char *buitlin)
{
	pid_t pid;
   int 	x;

	pid = 0;
	x = 0;
	pid = fork();
	if (pid < 0)
	{
		ft_putstr("\n\rerror forki\n");
		exit(-1);
	}
	else if (pid > 0)
	{
		waitpid(pid, &x, 0);
		kill(pid,	SIGTERM);
	}
	else
	{
		if(execve(./buitl.c  builtin, NULL) == -1)
		{
			ft_putstr("\n\rerror execve\n");
			exit(-1);
		}
	}
}


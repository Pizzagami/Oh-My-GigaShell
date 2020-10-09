#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

void	built_in_cd(char *path)
{
	int fd;

	fd = open(path, O_RDONLY);
	if (!path)
		return;
	if (chdir(path) == -1)
	{
		perror("chdir()");
	}
	/*if (fd < 0) // verifier les differente erreurs (et perror?)
	{
		ft_putstr("cd: no such file or directory: ");
		ft_putstr(path);
	}
	else
	{
		chdir(path);
	}*/
	close(fd);
}

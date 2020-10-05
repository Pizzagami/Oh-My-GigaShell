#include "libft.h"
#include "get_next_line.h"
#include "minishell.h"
#include <fcntl.h>

int		main(int argc,char **argv, char **env)
{	
	(void)argc;(void)argv;
	int x;
	struct termios save_cano;
	struct termios save_nncano;
	t_hist	hist;
	t_arrow ar;

	ar.x = 0;
	ar.y = 0;
	hist.x = 0;
	x = 0;
	ft_init_tab(&hist);
	term_init(&save_cano, &save_nncano);
	file_histo(&hist);
	while(x != 3)
	{
		x = bashy(&hist, &ar);
		tcsetattr(0, TCSADRAIN, &save_cano);
		persecutor(&hist, &ar, env);
		tcsetattr(0, TCSADRAIN, &save_nncano);
	}
	ft_putstr("\n^C fin du programme\n");
	histo_file(&hist);
	tcsetattr(0, TCSADRAIN, &save_cano);
	return(0);
}

void	file_histo(t_hist *hist)
{
	int fd;
	int x;
	int g;

	x = 0;
	fd = open("historic.omgsh", O_RDONLY | O_APPEND);
	if (fd < 0)
		return;
	while ((g = get_next_line(fd, &(hist->tab[x]))) > 0)
		x++;
	hist->x = x;
	if (g < 0)
	{
		ft_putstr("GNL Error \n");
	}
	close(fd);
}
void	histo_file(t_hist *hist)
{
	int fd;
	int x;

	x = 0;
	fd = open("historic.omgsh", O_CREAT | O_RDWR | O_TRUNC, S_IRWXU);
	while (hist->x > x)
	{
		ft_putstr_fd(hist->tab[x], fd);
		ft_putstr_fd("\n",fd);
		free(hist->tab[x]);
		x ++;
	}
	close(fd);
}
#include "get_next_line.h"
#include "minishell.h"
void	free_env(t_env *env);

int		main(int argc,char **argv, char **env)
{
	(void)argc;(void)argv;
	int x;
	int y;
	t_env  *envi;
	struct termios save_cano;
	struct termios save_nncano;
	t_hist	hist;
	t_arrow ar;
	int	last_ret;
	t_multi	multi;

	multi.str = NULL;
	multi.type = 0;
	last_ret = 0;
	y = 0;
	ar.x = 0;
	ar.y = 0;
	hist.x = 0;
	x = 0;
	envi = NULL;
	dup_env(env, &envi);
	hist.cc = is_unicorn_set(envi);
	//ft_init_tab(&hist);
	term_init(&save_cano, &save_nncano);
	file_histo(&hist);
	while(1)
    {
        x = bashy(&hist, &ar, y);
        tcsetattr(0, TCSADRAIN, &save_cano);
        if (x == 3)
            break;
		multi.x = x;	
		y = multilines(&hist, envi, &last_ret, &multi);
        tcsetattr(0, TCSADRAIN, &save_nncano);
    }
    ft_putstr("\n^C fin du programme\n");
	histo_file(&hist);
	free_env(envi);
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
		ft_putstr("GNL Error in file Histo\n");
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
			ft_putchar_fd((char)1,fd);
			free(hist->tab[x]);
		x++;
	}
	free(hist->tab[x]);
	x = 0;
	close(fd);
}

void	free_env(t_env *env)
{
	t_env *tmp;
	while(env)
	{
		free(env->name);
		free(env->val);
		tmp = env;
		env = env->next;
		free(tmp);
	}
}

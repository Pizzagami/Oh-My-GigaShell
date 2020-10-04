#include "libft.h"
#include "minishell.h"

int main(int argc,char **argv, char **env)
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
	while(x != 3)
	{
		x = bashy(&hist, &ar);
		tcsetattr(0, TCSADRAIN, &save_cano);
		persecutor(&hist, &ar, env);
		tcsetattr(0, TCSADRAIN, &save_nncano);
	}
	ft_putstr("\n^C fin du programme\n");
	//free hist
	tcsetattr(0, TCSADRAIN, &save_cano);
	return(0);
}


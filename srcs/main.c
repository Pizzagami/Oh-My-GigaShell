#include "libft.h"
#include "minishell.h"

int main(int argc,char **argv, char **env)
{	
	(void)argc;(void)argv;
	int x;
	struct termios save;
	t_hist	hist;
	t_arrow ar;

	ar.x = 0;
	ar.y = 0;
	hist.x = 0;
	ft_init_tab(&hist);
	term_init(&save);
	x = bashy(&hist, &ar, env);
	if(x == 0)
		ft_putstr("\n\r^C fin du programme\n\r");
	//free hist
	tcsetattr(0, TCSADRAIN, &save);
	return(0);
}


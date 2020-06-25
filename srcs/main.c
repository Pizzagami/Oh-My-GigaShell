#include "libft.h"
#include "minishell.h"

int main(int argc,char **argv)
{	
	(void)argc;(void)argv;
	int x;
	struct termios save;
	t_hist	hist;

	hist.x = 0;
	term_init(&save);
	x = bashy(&hist);
	if(x == 0)
		ft_putstr("\b\b^C fin du programme\n\r");
	tcsetattr(0, TCSADRAIN, &save);
	return(0);
}


#include "libft.h"
#include "minishell.h"

int main(int argc,char **argv)
{	
	int x;
	struct termios save;

	term_init(&save);
	x = bashy();
	if(x == 0)
		ft_putstr("^C fin du programme \n");
	return(0);
}


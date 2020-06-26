#ifndef	MINISHELL_H
# define MINISHELL_H

#include <termios.h>


typedef struct		s_hist
{
	char	*tab[256];
	int		x;
}					t_hist;

void		term_init(struct termios *save);
void		parse(t_hist *hist, char *str);
char		caspe(char c, char *str);
char		*remalloc(char *str, char c);
int			bashy(t_hist *hist);


#endif

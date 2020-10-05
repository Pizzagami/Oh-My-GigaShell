#ifndef	MINISHELL_H
# define MINISHELL_H

#include <termios.h>


typedef struct		s_hist
{
	char	*tab[256];
	int		x;
}					t_hist;

typedef struct		s_arrow
{
	int		x;
	int		y;
}					t_arrow;

void		term_init(struct termios *save_cano, struct termios *save_nncano);
void		historic(t_hist *hist, char *str);
char		caspe(char c, char **str, t_arrow *ar, t_hist *hist);
char		*remalloc(char *str, char c);
int			bashy(t_hist *hist, t_arrow *ar);
int			persecutor(t_hist *hist, t_arrow *ar, char *env[]);
void		file_histo(t_hist *hist);
void		histo_file(t_hist *hist);
void 		ft_init_tab(t_hist *hist);


#endif

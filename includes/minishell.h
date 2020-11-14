#ifndef	MINISHELL_H
# define MINISHELL_H

#include <termios.h>
#include "token.h"

typedef struct	s_env
{
	char			*name;
	char 			*val;
	struct s_env 	*next;

}				t_env;

typedef struct		s_hist
{
	char	*tab[256];
	int		x;
	int		cc;
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
int			persecutor(t_hist *hist, t_arrow *ar, char *env[], int *last_ret);
void		file_histo(t_hist *hist);
void		histo_file(t_hist *hist);
void 		ft_init_tab(t_hist *hist);
void		setcolor(int *x);
int			is_unicorn_set(char **env);
t_token		*create_simple_token_list(char *str);
char		*create_str(char *str, int start, int len);
void		env_split(char *str, char **str1, char **str2);
void		dup_env(char **envp, t_env **env);
void		add_tail(char *var, t_env **first);
void		add_env_var(char *var, t_env **first);
char		*get_env_var(char *var, t_env *first);
int			find_and_replace(t_env **first, char *var);
void		tri_and_find(t_env *first);

#endif

#ifndef MINISHELL_H
# define MINISHELL_H

#define PATH_MAX 4096
#include <termios.h>
#include "token.h"
#include <unistd.h>
#include <fcntl.h>
#include "libft.h"
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>

typedef struct		s_listdir
{
	char	*name;
	struct	s_listdir *next;
}					t_listdir;

typedef struct		s_mx
{
	int		s;
	int		p;
	char	*str;
	char	*quot;
}					t_mx;

typedef struct		s_env
{
	char			*name;
	char			*val;
	int 			l_name;
	struct s_env 	*next;

}					t_env;

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

typedef struct		s_multi
{
	char	*str;
	int		type;
	int		x;
}					t_multi;

void up(char **str, t_arrow *ar, t_hist *hist);
void down(char **str, t_arrow *ar, t_hist *hist);
void right(char **str, t_arrow *ar, t_hist *hist);
void left(char **str, t_arrow *ar, t_hist *hist);

typedef void FLCH_CSP(char **str, t_arrow *ar, t_hist *hist);

int			add_matching_names(char *path, int sfdo, t_listdir **actual,
			char *patern);
void		add_list(t_listdir *actual, char *minipath, char **final);
int			recursive(char *str, char *patern, int rc, t_mx x);
int			gigastar(char *patern, char **final, char *home);
int			superstar(char *str, char *patern);
t_token		*first_link(t_token *a, char *home, t_token *first);
t_token		*other_links(t_token *a, char *home);
t_mx		init_mx(int p, int s);
int			numberstars(char *str);
void		dereplace_stars(char *str);
int			is_dir(char *path, char *file);
void		removedoublestars(char **str_p);
void		removechar(char **str, int x);
int			srcchar(char c, char *str);	
t_listdir	*new_maillon(t_listdir *actual, char *name);
void		free_list(t_listdir *a);
void		sort_list(t_listdir *a);
void		sort_list_dsm(t_listdir *a);
int			ft_strcmp1(char *s1, char *s2);
int			ft_strcmp2(char *s1, char *s2);
void		set_special_token(char c, t_token **token_current);
void		free_env(t_env *env);
void		mfree(char *str1, char *str2);
int			recurdir(char *patern, char *path, char *minipath, char **final);
void		term_init(struct termios *save_cano, struct termios *save_nncano);
void		historic(t_hist *hist, char *str);
char		caspe(char c, char **str, t_arrow *ar, t_hist *hist);
char		*remalloc(char *str, char c);
int			bashy(t_hist *hist, t_arrow *ar, int y);
int			persecutor(t_hist *hist, t_env *env, int *last_ret);
int			multilines(t_hist *hist, t_env *env, int *last_ret, t_multi *multi);
void		file_histo(t_hist *hist);
void		histo_file(t_hist *hist);
void		ft_init_tab(t_hist *hist);
void		setcolor(int *x);
int			is_unicorn_set(t_env *env);
t_token		*create_simple_token_list(char *str);
char		*create_str(char *str, int start, int len);
int			env_split(char *str, char **str1, char **str2);
void		dup_env(char **envp, t_env **env);
void		add_tail(char *var, t_env **first);
void		add_env_var(char *var, t_env **first);
char		*get_env_var(char *var, t_env *first);
int			find_and_replace(t_env **first, char *var);
void		tri_and_find(t_env *first);
void		tri_and_print(t_env *first);
void		add_char(char **str, int index, char c);
char		*str_up(char *str);
char		*str_low(char *str);
void		buitin_echo(char **str);
void		builtin_cd(char *path, t_env *env);
void		builtin_env(t_env *first);
void		builtin_export(char **var, t_env **first);
void		builtin_unset(char *var, t_env **env);
void		builtin_pwd(void);
char		*ft_strjoin_sep(char *s1, char *s2, char sep);

#endif

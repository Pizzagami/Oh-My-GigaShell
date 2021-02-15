/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braimbau <braimbau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 15:04:28 by selgrabl          #+#    #+#             */
/*   Updated: 2021/02/15 14:26:02 by braimbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define PATH_MAX 4096
# include "struct.h"
# include <errno.h>
# include <termios.h>
# include "token.h"
# include <unistd.h>
# include <fcntl.h>
# include "libft.h"
# include <dirent.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/signal.h>
# include <signal.h>

typedef void	t_flch_csp(char **str, t_arrow *ar, t_hist *hist);

int				is_exec(char *str);
void			up(char **str, t_arrow *ar, t_hist *hist);
void			down(char **str, t_arrow *ar, t_hist *hist);
void			right(char **str, t_arrow *ar, t_hist *hist);
void			left(char **str, t_arrow *ar, t_hist *hist);
void			home(char **str, t_arrow *ar, t_hist *hist);
void			endl(char **str, t_arrow *ar, t_hist *hist);
void			mult_down(char **str, t_arrow *ar, t_hist *hist, int x);
void			upanddown(char **str, t_hist *hist, int x);
void			env_val(char *str, char **str1, int i, int j);
int				split_verif(char *str, int *y);
void			printex(t_env *tmp);
void			auto_completion(void);
void			fleche_init(t_flch_csp *fleche_caspe[7]);
void			wright(t_arrow *ar, char *str);
char			*strdel(char *str, t_arrow *ar);
void			wleft(t_arrow *ar, char *str);
void			vleft(char c, char *str, int y);
void			vleft_ar(int x, t_arrow *ar, int len, char *str);
int				which_case(void);
char			*remalloc(char *str, char c);
char			*strput(char *str, t_arrow *ar, char c);
void			left(char **str, t_arrow *ar, t_hist *hist);
void			right(char **str, t_arrow *ar, t_hist *hist);
void			up(char **str, t_arrow *ar, t_hist *hist);
void			down(char **str, t_arrow *ar, t_hist *hist);
void			remove_char(char *str, int index);
void			replace_chars(char **pstr, char **pquot);
int				add_matching_names(char *path, int sfdo, t_listdir **actual,
			char *patern);
void			add_list(t_listdir *actual, char *minipath, char **final);
int				recursive(char *str, char *patern, int rc, t_mx x);
int				gigastar(char *patern, char **final, char *home);
int				superstar(char *str, char *patern);
t_token			*first_link(t_token *a, char *home, t_token *first);
t_token			*other_links(t_token *a, char *home);
t_mx			init_mx(int p, int s);
int				numberstars(char *str);
void			dereplace_stars(char *str);
int				is_dir(char *path, char *file);
void			removedoublestars(char **str_p);
void			removechar(char **str, int x);
int				srcchar(char c, char *str);
t_listdir		*new_maillon(t_listdir *actual, char *name);
void			free_list(t_listdir *a);
void			sort_list(t_listdir *a);
void			sort_list_dsm(t_listdir *a);
int				ft_strcmp1(char *s1, char *s2);
int				ft_strcmp2(char *s1, char *s2);
void			set_special_token(char c, t_token **token_current);
void			free_env(t_env *env);
void			mfree(char *str1, char *str2);
int				recurdir(char *patern, char *path, char *minpath, char **finl);
void			term_init(struct termios *cano, struct termios *nncano);
void			historic(t_hist *hist, char *str);
char			caspe(char c, char **str, t_arrow *ar, t_hist *hist);
char			*remalloc(char *str, char c);
int				bashy(t_hist *hist, t_arrow *ar, int *ec);
int				persecutor(t_hist *hist, t_env *env, int *last_ret);
int				multilines(t_hist *hist, t_env *env, int *lret, t_multi *mult);
void			file_histo(t_hist *hist, char *path);
void			histo_file(t_hist *hist, char *path);
void			ft_init_tab(t_hist *hist);
void			setcolor(int *x);
int				is_unicorn_set(t_env *env);
t_token			*create_simple_token_list(char *str);
char			*create_str(char *str, int start, int len);
int				env_split(char *str, char **str1, char **str2);
void			dup_env(char **envp, t_env **env);
void			add_tail(char *var, t_env **first);
void			add_env_var(char *var, t_env **first);
char			*get_env_var(char *var, t_env *first);
int				find_and_replace(t_env **first, char *var);
void			tri_and_find(t_env *first);
void			triex(t_env *first);
void			add_char(char **str, int index, char c);
char			*str_up(char *str);
char			*str_low(char *str);
void			buitin_echo(char **str);
int				builtin_cd(char *path, t_env *env);
void			builtin_env(t_env *first);
void			builtin_export(char **var, t_env **first);
void			builtin_unset(char **var, t_env **env);
void			builtin_pwd(t_env *env);
void			builtin_exit(t_env *env, char **tab);
char			*ft_strjoin_sep(char *s1, char *s2, char sep);
void			delete_unquoted_newlines(char *str, char *quot);
int				esc_bksl(int *x, int *i, char *str, char *quot);

#endif

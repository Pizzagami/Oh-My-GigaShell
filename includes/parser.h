/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selgrabl <selgrabl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 16:13:31 by raimbault         #+#    #+#             */
/*   Updated: 2021/01/28 11:23:08 by selgrabl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "struct.h"
# include "token.h"
# include <unistd.h>
# include <string.h>
# include <errno.h>
# include <fcntl.h>
# include "libft.h"
# include <sys/types.h>
# include <sys/wait.h>
# include <dirent.h>
# include "minishell.h"

int				poor_bashy(char *eof, char **str, struct termios	save_cano,
	struct termios	save_nncano);
void			set_heredoc(t_redirection *redir, int *ec, int ret, char *str);
void			heredoc_list(t_list *list, int *ec);
void			heredoc_input(t_input *input, int *ec);
void			son_pipeline(int pfd[2], t_omm *omm, t_pipeline *pipeline);
void			exec_binary_son(t_omm omm, t_token *token, char **tab,
				char **tabenv);
void			clean_token_list(t_token *token);
void			free_tab(char **tabenv);
t_input			*parse_input(t_token *token_start, int *ec);
t_list			*parse_list(t_token *token_start, t_token *max, int *ec);
t_andor			*parse_andor(t_token *token_start, t_token *max, int *ec);
t_pipeline		*parse_pipeline(t_token *token_start, t_token *max, int *ec);
t_command		*parse_command(t_token *token_start, t_token *max, int *ec);
t_redirection	*parse_redirection(t_token *token_start, t_token *max, int *ec);
t_instruction	*parse_instruction(t_token *token_start, t_token *max, int *ec);
void			clean_list(t_list *list);
void			clean_input(t_input *input);
void			clean_andor(t_andor *andor);
void			display_input(t_input *input, int i);
void			printf_token(t_token *start);
char			*create_str(char *str, int start, int len);
int				is_special_char(char c);
int				double_brackets(t_token *start, t_token *max);
int				print_error(int *ec, int error);
int				is_in_brackets(t_token *token, t_token *start);
void			display_list(t_list *list, int i);
void			display_andor(t_andor *andor, int i);
void			display_pipeline(t_pipeline *pipeline, int i);
void			display_command(t_command *command, int i);
void			display_instruction(t_instruction *instruction, int i);
void			display_redirection(t_redirection *redirection, int i);
void			clean_command(t_command *command);
int				exec_input(t_input *input, t_omm omm);
int				exec_list(t_list *list, t_omm omm);
int				exec_andor(t_andor *andor, t_omm omm);
int				exec_pipeline(t_pipeline *pipeline, t_omm omm);
int				exec_command(t_command *command, t_omm omm);
int				exec_redirection(t_redirection *redirection, t_omm omm);
int				exec_instruction(t_instruction *instruction, t_omm omm);
int				ft_strcmp(char *s1, char *s2);
char			*lower_case(char *s);
t_omm			init_std_fd(t_env *env, int *last_ret);
char			**create_tab(t_token *start, t_token *max);
char			*get_path(t_env *env, char *str);
char			*get_env(t_env *env, char *key);
char			**get_env2(t_env *env, char *key);
void			reset_fd(t_omm omm);
t_token			*starize_list(t_token *a, t_token *max, char *home);
void			replace_dollar(t_token *a, t_omm omm);
int				is_builtin(char *executable);
int				exec_builtin(char *executable, char **tab, t_env *env);
char			*quote_string(char **pstr, int *ec);
#endif

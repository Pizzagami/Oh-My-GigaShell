/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selgrabl <selgrabl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 16:13:31 by raimbault         #+#    #+#             */
/*   Updated: 2021/01/28 11:19:09 by selgrabl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include <termios.h>
# include "token.h"

typedef struct				s_cell
{
	int x;
	int y;
	int len;
	int nb;
	int llx;
}							t_cell;

typedef struct				s_term
{
	struct termios	save_cano;
	struct termios	save_nncano;
}							t_term;

typedef	struct				s_pos
{
	int x;
	int y;
}							t_pos;

typedef struct				s_listdir
{
	char				*name;
	struct s_listdir	*next;
}							t_listdir;

typedef struct				s_mx
{
	int		s;
	int		p;
	char	*str;
	char	*quot;
}							t_mx;

typedef struct				s_env
{
	char			*name;
	char			*val;
	int				l_name;
	struct s_env	*next;

}							t_env;

typedef struct				s_hist
{
	char	*tab[256];
	int		x;
	int		y;
	int		cc;
}							t_hist;

typedef struct				s_arrow
{
	int		x;
	int		y;
}							t_arrow;

typedef struct				s_multi
{
	char	*str;
	int		type;
	int		x;
}							t_multi;

typedef struct				s_all
{
	int		x;
	t_env	*tenv;
	t_term	term;
	t_hist	thist;
	t_arrow	tar;
	t_multi	tmulti;
}							t_all;

typedef struct				s_omm
{
	int		stdin;
	int		stdout;
	int		*last_ret;
	t_env	*env;
}							t_omm;

typedef struct				s_instruction
{
	t_token	*start;
	t_token	*max;
}							t_instruction;

typedef struct				s_redirection
{
	t_type					type;
	char					*filename;
	struct s_redirection	*brother;
}							t_redirection;

typedef struct				s_command
{
	struct s_list			*c_list;
	struct s_instruction	*instruction;
	t_redirection			*redirection;
}							t_command;

typedef struct				s_pipeline
{
	struct s_pipeline	*brother;
	struct s_command	*command;
}							t_pipeline;

typedef struct				s_andor
{
	struct s_andor	*brother;
	t_pipeline		*pipeline;
	t_type			type;
}							t_andor;

typedef struct				s_list
{
	struct s_list	*brother;
	t_andor			*andor;
}							t_list;

typedef struct				s_input
{
	t_list	*list;
}							t_input;

#endif

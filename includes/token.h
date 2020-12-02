/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raimbaultbrieuc <marvin@42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 14:55:58 by raimbault         #+#    #+#             */
/*   Updated: 2020/12/01 16:25:26 by braimbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include <stdlib.h>
# include <stdio.h>

typedef enum	e_char
{
	CVOID,
	CSTAR,
	CDOLLAR,
	CDOLLEND
}				t_char;

typedef enum	e_type
{
	VOID,
	WORD,
	NAME,
	NEWLINE,
	OBRA,
	CBRA,
	STAR,
	QUOTE,
	DQUOTE,
	SEMI,
	AND_IF,
	OR_IF,
	PIPE,
	AND,
	LESS,
	DLESS,
	GREAT,
	DGREAT
}				t_type;

typedef struct	s_token
{
	t_type			type;
	char			*str;
	struct s_token	*next;
}				t_token;

t_token			*create_token_list(char *input, char *quot);
t_type			define_type(char *str);
int				ft_strcmp(char *s1, char *s2);
void			add_token(t_token **token_current, t_type type, char *str);
void			add_token_malloc(t_token **token_current, t_type type,
				char *str, int s);

#endif

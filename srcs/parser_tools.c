/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raimbaultbrieuc <marvin@42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 16:23:29 by raimbault         #+#    #+#             */
/*   Updated: 2021/01/19 14:06:15 by braimbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int		double_brackets(t_token *start, t_token *max)
{
	int i;

	i = 0;
	while (start)
	{
		if (start->type == OBRA)
			i++;
		if (start->type == CBRA)
			i--;
		if (start->next == max)
			return (1);
		if (i < 1)
			return (0);
		start = start->next;
	}
	return (1);
}

char	**create_str_tab(void)
{
	char **ret;

	ret = malloc(sizeof(char *) * 20);
	ret[0] = NULL;
	ret[1] = NULL;
	ret[2] = NULL;
	ret[3] = "Error : Missing character(s) after backslash\n";
	ret[4] = "Error : Malloc error while parsing input\n";
	ret[5] = "Error : Malloc error while parsing list\n";
	ret[6] = "Error : Missing element(s) before semicolon\n";
	ret[7] = NULL;
	ret[8] = "Error : Malloc while parsing andir\n";
	ret[9] = "Error : Missing element(s) before && or ||\n";
	ret[10] = "Error : Malloc error while parsing pipeline\n";
	ret[11] = "Error : Missing element(s) before pipe\n";
	ret[12] = NULL;
	ret[13] = NULL;
	ret[14] = "Error : Void paranthesis\n";
	ret[15] = "Error : Parsing error with paranthesis\n";
	ret[16] = "Error : Missing opening paranthesis\n";
	ret[17] = "Error : Missing file after redirection\n";
	ret[18] = "Error : feature not supported\n";
	ret[19] = "Error : Wrong character after || or &&\n";
	ret[20] = "Error : Can't create file for heredoc\n";
	return (ret);
}

int		print_error(int *ec, int error)
{
	char **tab;

	tab = create_str_tab();
	ft_putstr(tab[error]);
	*ec = error;
	free(tab);
	return (error);
}

int		is_in_brackets(t_token *token, t_token *start)
{
	int i;

	i = 0;
	while (start)
	{
		if (start->type == OBRA)
			i++;
		if (start->type == CBRA)
			i--;
		if (start == token)
			return (i);
		start = start->next;
	}
	return (0);
}

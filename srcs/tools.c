/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braimbau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 16:12:26 by braimbau          #+#    #+#             */
/*   Updated: 2020/12/21 16:17:10 by braimbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include "parser.h"

void	printf_token(t_token *token_o)
{
	int		i;
	t_token *token;

	token = token_o;
	i = 0;
	while (token)
	{
		printf("token nᵒ %d : _%s_ type = %d\n", i, token->str, token->type);
		i++;
		token = token->next;
	}
}

void	ft_init_tab(t_hist *hist)
{
	int x;

	x = 0;
	while (x < 256)
	{
		hist->tab[x] = malloc(sizeof(char));
		hist->tab[x][0] = 0;
		x++;
	}
}

char	*str_up(char *s)
{
	int i;

	i = 0;
	while (s && s[i])
	{
		if (s[i] >= 'a' && s[i] <= 'z')
			s[i] -= 32;
		i++;
	}
	return (s);
}

char	*str_low(char *s)
{
	int i;

	i = 0;
	while (s && s[i])
	{
		if (s[i] >= 'A' && s[i] <= 'Z')
			s[i] += 32;
		i++;
	}
	return (s);
}

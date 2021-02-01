/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grand_remplacement.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braimbau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 16:13:58 by braimbau          #+#    #+#             */
/*   Updated: 2021/02/01 10:04:20 by braimbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include "parser.h"

char	*replace_occurence(char *str, char *to_rep, char *rep_by)
{
	int		i;
	char	*tmp;
	char	*ret;

	ret = NULL;
	i = ft_findstr(str, to_rep);
	ret = ft_substr(str, 0, i);
	tmp = ret;
	ret = ft_strjoin(ret, rep_by);
	free(tmp);
	tmp = ret;
	ret = ft_strjoin(ret, str + i + ft_strlen(to_rep));
	free(tmp);
	return (ret);
}

char	*replace_occurences(char *str, char *to_rep, char *rep_by)
{
	char *tmp;

	tmp = NULL;
	while (ft_findstr(str, to_rep) != -1)
	{
		str = replace_occurence(str, to_rep, rep_by);
		if (tmp)
			free(tmp);
		tmp = str;
	}
	return (str);
}

void	multi_free(char *s1, char *s2, char *s3, char *s4)
{
	if (s1)
		free(s1);
	if (s2)
		free(s2);
	if (s3)
		free(s3);
	if (s4)
		free(s4);
}

void	replace_dollar(t_token *a, t_omm omm, char i, char *key)
{
	char *tmp;
	char *value;
	char *subkey;

	while (a && (a->type < SEMI || a->type > PIPE))
	{
		i = ft_strfind(a->str, CDOLLAR);
		while (i != -1)
		{
			if (a->str[i + 1] == CDOLLEND && (a->str[i + 1] = '$'))
				return ;
			key = ft_substr(a->str, i, ft_strfind(a->str, CDOLLEND) - i + 1);
			subkey = ft_substr(key, 1, ft_strlen(key) - 2);
			value = NULL;
			tmp = a->str;
			if (key[1] == '?' && ft_strlen(key) == 3)
				value = ft_itoa(*(omm.last_ret));
			else if (get_env(omm.env, subkey))
				value = ft_strdup(get_env(omm.env, subkey));
			a->str = replace_occurence(a->str, key, value);
			i = ft_strfind(a->str, CDOLLAR);
			multi_free(tmp, key, subkey, value);
		}
		a = a->next;
	}
}

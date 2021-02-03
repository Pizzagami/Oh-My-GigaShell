/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selgrabl <selgrabl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 11:49:38 by braimbau          #+#    #+#             */
/*   Updated: 2021/02/03 14:12:39 by braimbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h"
#include "get_next_line.h"
#include <time.h>

char	*rdmstr(int n)
{
	char	*str;
	int		i;

	i = 0;
	str = malloc(sizeof(char) * n + 1);
	srand(time(NULL));
	while (i < n)
	{
		str[i] = rand() % 26 + 'a';
		i++;
	}
	str[i] = 0;
	return (str);
}

void	set_heredoc(t_redirection *redir, int *ec, int ret, char *str)
{
	char			*buf;
	int				fd;
	t_term			t;
	char *tmp;

	term_init(&t.save_cano, &t.save_nncano);
	ft_putstr(">");
	ret = poor_bashy(redir->filename, &buf, t.save_cano, t.save_nncano);
	while (ret < 2 && ft_strcmp(buf, redir->filename))
	{
		(ret == -1) ? print_error(ec, 20) : 0;
		tmp = str;
		str = (str != NULL) ? ft_strjoin_sep(str, buf, '\n') : ft_strdup(buf);
		if (tmp)
			free(tmp);
		free(buf);
		ft_putstr(">\033[0m");
		ret = poor_bashy(redir->filename, &buf, t.save_cano, t.save_nncano);
	}
	free(buf);
	redir->filename = rdmstr(12);
	fd = open(redir->filename, O_WRONLY | O_CREAT, S_IRWXU);
	if (str)
	{
		(ret != 3) ? ft_putstr_fd(str, fd) : 0;
		ft_putchar_fd('\n', fd);
		free(str);
	}
	close(fd);
}

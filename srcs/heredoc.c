/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braimbau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 11:49:38 by braimbau          #+#    #+#             */
/*   Updated: 2021/01/20 10:04:11 by braimbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h"
#include "get_next_line.h"
#include "time.h"

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

void	set_heredoc(t_redirection *redirection, int *ec)
{
	char	*buf;
	char	*str;
	int		ret;
	int		fd;

	str = NULL;
	ft_putstr(">");
	ret = get_next_line(0, &buf, '\n');
	while (ret && ft_strcmp(buf, redirection->filename))
	{
		if (ret == -1)
			print_error(ec, 20);
		str = ft_strjoin_sep(str, buf, '\n');
		free(buf);
		ft_putstr(">");
		ret = get_next_line(0, &buf, '\n');
	}
	redirection->filename = rdmstr(12);
	fd = open(redirection->filename, O_WRONLY | O_CREAT, S_IRWXU);
	if (str)
	{
		ft_putstr_fd(str, fd);
		free(str);
	}
	close(fd);
}

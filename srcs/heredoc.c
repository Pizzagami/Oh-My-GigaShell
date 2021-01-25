/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selgrabl <selgrabl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 11:49:38 by braimbau          #+#    #+#             */
/*   Updated: 2021/01/25 15:03:31 by selgrabl         ###   ########.fr       */
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

void	set_heredoc(t_redirection *redirection, int *ec)
{
	char	*buf;
	char	*str;
	int		ret;
	int		fd;

	str = NULL;
	ft_putstr(">");
	ret = poor_bashy(redirection->filename, &buf);
	while (ret < 2 && ft_strcmp(buf, redirection->filename))
	{
		if (ret == -1)
			print_error(ec, 20);
		str = ft_strjoin_sep(str, buf, '\n');
		free(buf);
		ft_putstr(">\033[0m");
		ret = poor_bashy(redirection->filename, &buf);
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

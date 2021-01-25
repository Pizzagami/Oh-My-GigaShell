/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selgrabl <selgrabl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 11:49:38 by braimbau          #+#    #+#             */
/*   Updated: 2021/01/25 16:40:34 by selgrabl         ###   ########.fr       */
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
	struct termios	save_cano;
	struct termios	save_nncano;
	
	str = NULL;
	term_init(&save_cano, &save_nncano);
	ft_putstr(">");
	ret = poor_bashy(redirection->filename, &buf, save_cano, save_nncano);
	while (ret < 2 && ft_strcmp(buf, redirection->filename))
	{
		(void)ec;
		if (ret == -1)
			print_error(ec, 20);
		str = ft_strjoin_sep(str, buf, '\n');
		free(buf);
		ft_putstr(">\033[0m");
		ret = poor_bashy(redirection->filename, &buf, save_cano, save_nncano);
	}
	redirection->filename = rdmstr(12);
	fd = open(redirection->filename, O_WRONLY | O_CREAT, S_IRWXU);
	if (str)
	{
		if (ret != 3)
			ft_putstr_fd(str, fd);
		free(str);
	}
	close(fd);
}

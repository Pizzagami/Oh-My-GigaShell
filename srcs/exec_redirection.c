/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braimbau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 11:09:48 by braimbau          #+#    #+#             */
/*   Updated: 2021/01/19 11:24:18 by braimbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "get_next_line.h"

int		great_redirection(t_redirection *redirection)
{
	int fd;

	fd = open(redirection->filename, O_CREAT | O_RDWR | O_TRUNC, S_IRWXU);
	if (fd == -1)
	{
		perror("Error:");
		return (1);
	}
	dup2(fd, 1);
	close(fd);
	return (0);
}

int		greater_redirection(t_redirection *redirection)
{
	int fd;

	fd = open(redirection->filename, O_CREAT | O_RDWR | O_APPEND);
	if (fd == -1)
	{
		printf("Error : %s\n", strerror(errno));
		return (1);
	}
	dup2(fd, 1);
	close(fd);
	return (0);
}

int		less_redirection(t_redirection *redirection)
{
	int fd;

	fd = open(redirection->filename, O_RDONLY);
	if (fd == -1)
	{
		printf("Error : %s\n", strerror(errno));
		return (1);
	}
	dup2(fd, 0);
	close(fd);
	return (0);
}

int		lesser_redirection(t_redirection *redirection)
{
	char	*buf;
	char	*str = "";
	int		ret;

	ft_putstr(">");
	ret = get_next_line(0, &buf);
	while (ret && ft_strcmp(buf, redirection->filename))
	{
		if (ret == -1)
			; //gerer cette erreur
		str = ft_strjoin_sep(str, buf, '\n');
		free(buf);
		ft_putstr(">");
		ret = get_next_line(0, &buf);
	}
	int fd = open(".tempfile", O_WRONLY | O_CREAT);
	ft_putstr_fd(str, fd);
	close(fd);
	fd = open(".tempfile", O_RDONLY);
	dup2(fd, 0);
	close(fd);
	remove(".tempfile");
	return (0);
}

int		exec_redirection(t_redirection *redirection, t_omm omm)
{
	if (redirection && redirection->type == GREAT &&
			great_redirection(redirection))
		return (1);
	else if (redirection && redirection->type == DGREAT
			&& greater_redirection(redirection))
		return (1);
	else if (redirection && redirection->type == LESS
			&& less_redirection(redirection))
		return (1);
	else if (redirection && redirection->type == DLESS
			&& lesser_redirection(redirection))
		return (1);
	else if (0)
	{
		if (omm.stdout != 1)
			dup2(omm.stdout, 1);
		if (omm.stdin != 0)
			dup2(omm.stdin, 0);
	}
	if (redirection && redirection->brother)
	{
		redirection = redirection->brother;
		exec_redirection(redirection, omm);
	}
	return (0);
}

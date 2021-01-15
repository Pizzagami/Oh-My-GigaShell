/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braimbau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 11:09:48 by braimbau          #+#    #+#             */
/*   Updated: 2021/01/15 10:31:00 by braimbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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

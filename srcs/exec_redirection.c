/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selgrabl <selgrabl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 11:09:48 by braimbau          #+#    #+#             */
/*   Updated: 2021/01/26 17:23:07 by selgrabl         ###   ########.fr       */
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
	int fd;

	fd = open(redirection->filename, O_RDONLY);
	dup2(fd, 0);
	close(fd);
	remove(redirection->filename);
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
	if (redirection && redirection->brother)
	{
		redirection = redirection->brother;
		exec_redirection(redirection, omm);
	}
	return (0);
}

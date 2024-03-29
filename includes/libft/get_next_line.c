/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selgrabl <selgrabl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 15:03:19 by selgrabl          #+#    #+#             */
/*   Updated: 2021/01/28 10:47:54 by selgrabl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	**init(char **line, char **buf, int fd)
{
	int x;

	if (!(*line = malloc(sizeof(char))))
		return (NULL);
	(*line)[0] = 0;
	if (!buf)
	{
		if (!(buf = malloc(sizeof(char *) * 10240)))
			return (NULL);
		x = 0;
		while (x < 10240)
		{
			buf[x] = NULL;
			x++;
		}
	}
	if (buf[fd] == NULL)
	{
		if (!(buf[fd] = malloc(sizeof(char) * (32 + 1))))
			return (NULL);
		buf[fd][0] = 0;
	}
	return (buf);
}

int		get_next_line(int fd, char **line, char c)
{
	static char		**buf;
	int				x;

	if (line == 0 || fd < 0)
		return (-1);
	buf = init(line, buf, fd);
	while (1)
	{
		x = -1;
		if (buf[fd][0] == 0)
		{
			while (x++ < 32)
				buf[fd][x] = 0;
			x = read(fd, buf[fd], 32);
			if (x < 1)
				return (clear_buff(x, fd, &buf));
		}
		x = 0;
		while (buf[fd][x] && buf[fd][x] != c)
			x++;
		join(line, &buf[fd], x);
		if (buf[fd][0] == c)
			return (increase_buf(&buf[fd]));
	}
}

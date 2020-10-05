/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selgrabl <selgrabl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 10:44:52 by selgrabl          #+#    #+#             */
/*   Updated: 2020/10/05 18:03:30 by selgrabl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int		ft_strlen(char *str)
{
	int i;

	i = 0;
	while (*str != 0)
	{
		i++;
		str++;
	}
	return (i);
}

int		increase_buf(char **buf)
{
	int x;

	x = 0;
	while ((*buf)[x])
	{
		(*buf)[x] = (*buf)[x + 1];
		x++;
	}
	return (1);
}

void	join(char **line, char **buf, int x)
{
	int		i;
	int		j;
	int		a;
	char	*tmp;

	a = 0;
	i = (*line) ? ft_strlen(*line) : 0;
	j = x;
	tmp = *line;
	if (!(*line = malloc(sizeof(char) * (i + j + 1))))
		exit(0);
	while (a < i)
	{
		(*line)[a] = tmp[a];
		a++;
	}
	free(tmp);
	a = -1;
	while (++a < j)
		(*line)[i + a] = (*buf)[a];
	(*line)[i + j] = '\0';
	while (a--)
		increase_buf(buf);
}

int		clear_buff(int x, int fd, char ***buf)
{
	char	**buff;
	int		i;

	buff = *buf;
	i = 0;
	free(buff[fd]);
	buff[fd] = NULL;
	while (i < 10240 && buff && buff[i] == NULL)
		i++;
	if (i == 10240 && buff != NULL)
	{
		free(*buf);
		*buf = NULL;
	}
	return ((x == 0) ? 0 : -1);
}

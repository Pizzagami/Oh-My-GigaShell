/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_histo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selgrabl <selgrabl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 10:23:00 by selgrabl          #+#    #+#             */
/*   Updated: 2021/01/27 17:08:49 by selgrabl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "get_next_line.h"

void	file_histo(t_hist *hist, char *path)
{
	int fd;
	int x;
	int g;

	x = 0;
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return ;
	while ((g = get_next_line(fd, &(hist->tab[x]), (char)1)) > 0)
		x++;
	hist->x = x;
	if (g < 0)
	{
		ft_putstr("GNL Error in file Histo\n");
	}
	close(fd);
}

void	histo_file(t_hist *hist, char *path)
{
	int fd;
	int x;

	x = 0;
	fd = open(path, O_CREAT | O_RDWR | O_TRUNC, S_IRWXU);
	while (hist->x > x)
	{
		ft_putstr_fd(hist->tab[x], fd);
		ft_putchar_fd((char)1, fd);
		x++;
	}
	close(fd);
}

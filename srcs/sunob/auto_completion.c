/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_completion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braimbau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 08:58:51 by braimbau          #+#    #+#             */
/*   Updated: 2021/01/27 12:03:31 by braimbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/ioctl.h>
#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include "minishell.h"

t_listdir	*get_files(char *path, int fo)
{
	DIR				*dir;
	struct dirent	*dirent;
	t_listdir		*a;
	t_listdir		*new;

	a = NULL;
	dir = opendir(path);
	if (dir == NULL)
		return (NULL);
	while((dirent = readdir(dir)) && (fo == 0 || !is_dir("./", dirent->d_name)))
	{
		if (dirent->d_name[0] != '.')
		{
			new = malloc(sizeof(t_listdir));
			new->next = a;
			new->name = dirent->d_name;
			a = new;
		}
	}
	return (a);
}

int	list_mlen(t_listdir *list)
{
	int mlen;

	mlen = 0;
	while (list)
	{
		if ((int)ft_strlen(list->name) > mlen)
			mlen = ft_strlen(list->name);
		list = list->next;
	}
	return (mlen);
}

int	list_len(t_listdir *list)
{
	int len;

	len = 0;
	while (list)
	{
		len++;
		list = list->next;
	}
	return (len);
}

t_cell	get_cell(t_listdir *list)
{
	t_cell cell;
	struct		winsize size;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
	cell.len = list_mlen(list);
	cell.nb = list_len(list);
	cell.len = cell.len + 4 - cell.len % 4;
	cell.x = size.ws_col / cell.len;
	cell.x = (cell.x) ? cell.x : 1;
	if (cell.x > cell.nb)
		cell.x = cell.nb;
	cell.y = cell.nb / cell.x;
	if (cell.x * cell.y < cell.nb)
	{
		cell.llx = cell.nb - cell.x * cell.y;
		cell.y++;
	}
	else
		cell.llx = cell.x;
	return (cell);
}

void	add_spaces(char *name, t_cell cell)
{
	int x;

	x = cell.len - ft_strlen(name);
	while (x)
	{
		write(1," ", 1);
		x--;
	}
}

void	reset_cursor(t_pos *pos)
{
	while (pos->x)
	{
		pos->x--;
		ft_putstr("\b");
	}
	pos->y--;
	while (pos->y)
	{
		pos->y--;
		ft_putstr("\x1b[A");
	}
}

void	display_cells(t_cell cell, t_listdir *list, t_pos *pos)
{
	int y;
	int x;

	printf("\n");
	y = 0;
	while (y < cell.y)
	{
		x = 0;
		while (x < cell.x && list)
		{
			ft_putstr(list->name);
			add_spaces(list->name, cell);
			list = list->next;
			x++;
		}
		y++;
		if (y < cell.y)
			printf("\n");
		pos->x = x * cell.len + 1;
		pos->y = y;
	}
	reset_cursor(pos);
}

void auto_completion(void)
{
	t_listdir	*list;
	t_cell		cell;
	t_pos		pos;

	list = get_files(".", 0);
	cell = get_cell(list);
	display_cells(cell, list, &pos);

	
}

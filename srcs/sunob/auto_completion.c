/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_completion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braimbau <braimbau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 08:58:51 by braimbau          #+#    #+#             */
/*   Updated: 2021/01/29 11:32:34 by braimbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/ioctl.h>
#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include "minishell.h"

int mlen_list(t_listdir *a)
{
	int mlen;
	int len;

	mlen = 0;
	while (a)
	{
		len = ft_strlen(a->name);
		if (len > mlen)
			mlen = len;
		a = a->next;
	}
	return (mlen);
}

int len_list(t_listdir *a)
{
	int x;

	x = 0;
	while (a)
	{
		x++;
		a = a->next;
	}
	return (x);
}

t_cell get_cell(t_listdir *list)
{
	t_cell cell;
	struct winsize size;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
	cell.len = mlen_list(list) + 2;
	cell.x = size.ws_col / cell.len;
	cell.nb = len_list(list);
	if (cell.x > cell.nb)
	{
		cell.x = cell.nb;
		cell.y = cell.nb / cell.x;
	}
	if (cell.y == 1)
		cell.llx = cell.x;
	else if (cell.x * cell.y != cell.nb)
	{
		cell.y++;
		cell.llx = cell.nb - cell.x * cell.y;
	}
	else
		cell.llx = cell.x;
	return (cell);
}

char *last_word(char *str)
{
	int x;
	int i;

	x = ft_strlen(str) - 1;
	while (x && str[x] == ' ')
		x--;
	i = x;
	while (i && str[x] != ' ')
		i--;
	return (ft_substr(str, i, x - i + 1));
}

void	set_cur(t_pos pos)
{
	while (pos.x)
	{
		ft_putstr("\033[C");
		pos.x--;
	}
	while (pos.y)
	{
		ft_putstr("\033[B");
		pos.y--;
	}
}

void	reset_cursor(t_pos pos)
{
	while (pos.x)
	{
		ft_putstr("\033[D");
		pos.x--;
	}
	while (pos.y)
	{
		ft_putstr("\033[A");
		pos.y--;
	}
}

void	add_spaces(char *str, int len)
{
	int x;

	x = len - (int)ft_strlen(str);
	while (x)
	{
		x--;
		ft_putchar(' ');
	}
}

t_pos init_pos(int x, int y)
{
	t_pos pos;

	pos.x = x;
	pos.y = y;
	return (pos);
}

char *get_name(t_listdir *a, int i)
{
	int x = 0;

	while (a)
	{
		if (x == i)
			return (a->name);
		a = a->next;
		x++;
	}
	return (NULL);
}

void highlight_cell(t_cell cell, t_pos pc, t_listdir *list)
{
	char    *name;
	t_pos   pcur;

	name = get_name(list, pc.y * cell.x + pc.x);
	ft_putstr("\n");
	set_cur(init_pos(pc.x * cell.len, pc.y));
	ft_putstr("\033[0;30;47m");
	ft_putstr(name);
	add_spaces(name, cell.len - 2);
	ft_putstr("\033[0m");
	pcur.x = (pc.x + 1) * cell.len + 1;
	pcur.y = pc.y + 1;
	reset_cursor(pcur);
}

void deshighlight_cell(t_cell cell, t_pos pc, t_listdir *list)
{
	char    *name;
	t_pos   pcur;

	name = get_name(list, pc.y * cell.x + pc.x);
	ft_putstr("\n");
	set_cur(init_pos(pc.x * cell.len, pc.y));
	ft_putstr(name);
	add_spaces(name, cell.len -2);
	pcur.x = (pc.x + 1) * cell.len + 1;
	pcur.y = pc.y + 1;
	reset_cursor(pcur);
}

void   clear_cells(t_cell cell)
{
	int             y;
	int             x;
	t_pos   pcur;

	ft_putstr("\n");
	y = 0;
	while (y < cell.y)
	{
		x = 0;
		while (x < cell.len * cell.x)
		{
			ft_putstr(" ");
			x++;
		}
		y++;
		if (y < cell.y)
			printf("\n");
		pcur.x = x * cell.len + 1;
		pcur.y = y;
	}
	reset_cursor(pcur);
}

void   append_line(char **str, t_cell cell, t_pos pos, t_listdir *list)
{
	char *tmp;
	char *name;

	name = get_name(list, pos.y * cell.x + pos.x);
	tmp = ft_strjoin(*str, name);
	set_cur(init_pos(10, 0));
	ft_putstr(tmp);
	free(tmp);
}

void   desappend_line(char **str, t_cell cell, t_pos pos, t_listdir *list)
{
	int x;
	char *name;

	x = ft_strlen(*str);
	set_cur(init_pos(10 + x, 0));
	name = get_name(list, pos.y * cell.x + pos.x);
	x = ft_strlen(name);
	while (x)
	{
		x--;
		ft_putstr(" ");
	}
	ft_putstr("\r");
}

t_listdir *get_files(char *path, int d)
{
	DIR *dir;
	struct dirent *dirent;
	t_listdir *a;
	t_listdir *new;

	a = NULL;
	dir = opendir(path);
	if (dir == NULL)
		return (NULL);
	while ((dirent = readdir(dir)))
	{
		if (dirent->d_name[0] != '.' && (d == 0 || is_dir(".", dirent->d_name)))
		{
			new = malloc(sizeof(t_listdir));
			new->next = a;
			new->name = dirent->d_name;
			a = new;
		}
	}
	return (a);
}

void	display_cells(t_listdir *list, t_cell cell)
{
	int y;
	int x;
	char *name;

	printf("\n");
	y = 0;
	while (y < cell.y)
	{
		x = 0;
		while (x < cell.x)
		{
			name = get_name(list, y * cell.x + x);
			ft_putstr(name);
			add_spaces(name, cell.len);
			x++;
		}
		printf("\n");
		y++;
	}
	reset_cursor(init_pos(x * cell.x, y + 1));
}

t_listdir *chose_list(char *str)
{
	int	x;
	char	*lw;

	x = ft_strlen(str) - 1;
	if (str[x] == ' ')
	{
		lw = last_word(str);
		if (strcmp(lw, "cd") == 0)
		{
			free(lw);
			return (get_files(".", 1));
		}
		else
		{
			free(lw);
			return (get_files(".", 0));
		}
	}
	printf("heu bro c la merde\n");
	return (NULL);
}

void auto_completion(char **str)
{
	t_listdir       *list;
	t_cell          cell;
	char            buf[1];
	t_pos           pos;
	char            *tmp;

	list = chose_list(*str);
	cell = get_cell(list);
	display_cells(list, cell);
	set_cur(init_pos(10 + ft_strlen(*str), 0));
	pos.x = 0;
	pos.y = 0;
	highlight_cell(cell, pos, list);
	append_line(str, cell, pos, list);
	while (1)
	{
		read(0, buf, 1);
		if (buf[0] == 127)
		{
			clear_cells(cell);
			desappend_line(str, cell, pos, list);
			set_cur(init_pos(10 + ft_strlen(*str), 0));
			break;
		}
		if (buf[0] == 10)
		{
			tmp = *str;
			*str = ft_strjoin(*str, get_name(list, pos.y * cell.x + pos.x));
			free(tmp);
			tmp = *str;
			*str = ft_strjoin(*str, " ");
			free (tmp);
			clear_cells(cell);
			set_cur(init_pos(10 + ft_strlen(*str), 0));
			return ;
		}
		if (buf[0] == 'd' && pos.x < cell.x - 1 && (pos.y < cell.y - 1 || pos.x < cell.llx - 1))
		{
			deshighlight_cell(cell, pos, list);
			desappend_line(str, cell, pos, list);
			pos.x++;
			highlight_cell(cell, pos, list);
			append_line(str, cell, pos, list);
		}
		else if (buf[0] == 'd' && pos.x == cell.x - 1 && pos.y != cell.y - 1)
		{
			deshighlight_cell(cell, pos, list);
			desappend_line(str, cell, pos, list);
			pos.x = 0;
			pos.y++;
			highlight_cell(cell, pos, list);
			append_line(str, cell, pos, list);
		}
		if (buf[0] == 'a' && pos.x)
		{
			deshighlight_cell(cell, pos, list);
			desappend_line(str, cell, pos, list);
			pos.x--;
			highlight_cell(cell, pos, list);
			append_line(str, cell, pos, list);
		}
		else if (buf[0] == 'a' && pos.x == 0 && pos.y)
		{
			deshighlight_cell(cell, pos, list);
			desappend_line(str, cell, pos, list);
			pos.x = cell.x - 1;
			pos.y--;
			highlight_cell(cell, pos, list);
			append_line(str, cell, pos, list);
		}
		if (buf[0] == 'w' && pos.y)
		{
			deshighlight_cell(cell, pos, list);
			desappend_line(str, cell, pos, list);
			pos.y--;
			highlight_cell(cell, pos, list);
			append_line(str, cell, pos, list);
		}
		if (buf[0] == 's' && (pos.y < cell.y - 2 || (pos.y == cell.y - 2 && pos.x < cell.llx)))
		{
			deshighlight_cell(cell, pos, list);
			desappend_line(str, cell, pos, list);
			pos.y++;
			highlight_cell(cell, pos, list);
			append_line(str, cell, pos, list);
		}
	}
}

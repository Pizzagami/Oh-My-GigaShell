/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pizzagami <pizzagami@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 10:23:00 by braimbau          #+#    #+#             */
/*   Updated: 2021/01/24 22:01:02 by pizzagami        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "minishell.h"


void	langis(int sig)
{
	if (sig == 3)
		ft_putstr("Quit: 3\n");
	if (sig == 2)
		ft_putstr("\b\b  \b\b");
}

int		main(int argc, char **argv, char **env)
{
	int				x;
	t_env			*envi;
	struct termios	save_cano;
	struct termios	save_nncano;
	t_hist			hist;
	t_arrow			ar;
	int				last_ret;
	t_multi			multi;
	char			*path;
	
	(void)argc;
	(void)argv;
	multi.str = NULL;
	multi.type = 0;

	path = ft_calloc(1, 1024);
	ft_strlcat(getcwd(path, PATH_MAX - 1), "/historic.omgsh",ft_strlen(path) + 16);
	last_ret = 0;
	x = 0;
	ar.x = 0;
	ar.y = 0;
	hist.x = 0;
	hist.y = 0;
	envi = NULL;
	dup_env(env, &envi);
	hist.cc = is_unicorn_set(envi);
	term_init(&save_cano, &save_nncano);
	signal(SIGINT, langis);
	signal(SIGQUIT, langis);
	file_histo(&hist, path);
	while (1)
	{
		x = bashy(&hist, &ar);
		if (x != 3)
		{
			tcsetattr(0, TCSADRAIN, &save_cano);
			multi.x = x;
			hist.y = multilines(&hist, envi, &last_ret, &multi);
			histo_file(&hist, path);
			tcsetattr(0, TCSADRAIN, &save_nncano);
		}
	}
	tcsetattr(0, TCSADRAIN, &save_cano);
	return (0);
}

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
		//free(hist->tab[x]);
		x++;
	}
	//if (x != 0)
	//	free(hist->tab[x]);
	close(fd);
}

void	free_env(t_env *env)
{
	t_env *tmp;

	while (env)
	{
		free(env->name);
		free(env->val);
		tmp = env;
		env = env->next;
		free(tmp);
	}
}


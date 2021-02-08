/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selgrabl <selgrabl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 10:23:00 by braimbau          #+#    #+#             */
/*   Updated: 2021/02/08 23:34:24 by braimbau         ###   ########.fr       */
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

void	init_main(t_all *all, int *last_ret, int argc, char **argv)
{
	(void)argc;
	(void)argv;
	*last_ret = 0;
	all->multi.str = NULL;
	all->multi.type = 0;
	all->x = 0;
	all->ar.x = 0;
	all->ar.y = 0;
	all->hist.x = 0;
	all->hist.y = 0;
	all->env = NULL;
	signal(SIGINT, langis);
	signal(SIGQUIT, langis);
	term_init(&all->term.save_cano, &all->term.save_nncano);
}

int		main(int argc, char **argv, char **env)
{
	t_all			all;
	int				last_ret;
	char			*path;
	char			*path1[1024];

	path = ft_strjoin_sep(getcwd((char *)path1, 1023), "historic.omgsh", '/');
	init_main(&all, &last_ret, argc, argv);
	dup_env(env, &all.env);
	all.hist.cc = is_unicorn_set(all.env);
	file_histo(&all.hist, path);
	while (1)
	{
		all.x = bashy(&all.hist, &all.ar);
		if (all.x != 3)
		{
			tcsetattr(0, TCSADRAIN, &all.term.save_cano);
			all.multi.x = all.x;
			all.hist.y = multilines(&all.hist,
			all.env, &last_ret, &all.multi);
			histo_file(&all.hist, path);
			tcsetattr(0, TCSADRAIN, &all.term.save_nncano);
		}
	}
	tcsetattr(0, TCSADRAIN, &all.term.save_cano);
	return (0);
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

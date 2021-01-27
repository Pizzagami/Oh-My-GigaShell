/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selgrabl <selgrabl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 10:23:00 by braimbau          #+#    #+#             */
/*   Updated: 2021/01/27 16:54:13 by selgrabl         ###   ########.fr       */
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
	all->tmulti.str = NULL;
	all->tmulti.type = 0;
	all->x = 0;
	all->tar.x = 0;
	all->tar.y = 0;
	all->thist.x = 0;
	all->thist.y = 0;
	signal(SIGINT, langis);
	signal(SIGQUIT, langis);
	term_init(&all->term.save_cano, &all->term.save_nncano);
}

int		main(int argc, char **argv, char **env)
{
	t_all			all;
	int				last_ret;
	char			*path;

	path = ft_calloc(1, 1024);
	ft_strlcat(getcwd(path, 1023), "/historic.omgsh", ft_strlen(path) + 16);
	init_main(&all, &last_ret, argc, argv);
	dup_env(env, &all.tenv);
	all.thist.cc = is_unicorn_set(all.tenv);
	file_histo(&all.thist, path);
	while (1)
	{
		all.x = bashy(&all.thist, &all.tar);
		if (all.x != 3)
		{
			tcsetattr(0, TCSADRAIN, &all.term.save_cano);
			all.tmulti.x = all.x;
			all.thist.y = multilines(&all.thist,
			all.tenv, &last_ret, &all.tmulti);
			histo_file(&all.thist, path);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selgrabl <selgrabl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 14:45:18 by raimbault         #+#    #+#             */
/*   Updated: 2021/02/16 17:02:28 by braimbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <signal.h>

int		exec_andor(t_andor *andor, t_omm omm)
{
	int i;
	int a;

	a = 1;
	i = 0;
	reset_fd(omm);
	if (andor->pipeline)
		i = exec_pipeline(andor->pipeline, omm);
	while (andor->brother && a)
	{
		if (andor->type == AND_IF && !i)
		{
			i = exec_andor(andor->brother, omm);
			a = 0;
		}
		else if (andor->type == OR_IF && i)
		{
			i = exec_andor(andor->brother, omm);
			a = 0;
		}
		else
			andor = andor->brother;
	}
	return (i);
}

int		exec_pipeline(t_pipeline *pipeline, t_omm omm)
{
	int		i;
	int		pfd[2];
	int		pid;
	int		x;

	i = 0;
	if (pipeline->brother)
	{
		pipe(pfd);
		pid = fork();
		if (pid != 0)
		{
			close(pfd[1]);
			dup2(pfd[0], 0);
			close(pfd[0]);
			i = exec_pipeline(pipeline->brother, omm);
			waitpid(pid, &x, 0);
		}
		else
			son_pipeline(pfd, &omm, pipeline);
	}
	else if (pipeline->command)
		i = exec_command(pipeline->command, omm);
	return (i);
}

int		exec_command(t_command *command, t_omm omm)
{
	int i;

	i = exec_redirection(command->redirection, omm);
	if (i)
		return (i);
	if (command->instruction)
		i = exec_instruction(command->instruction, omm);
	if (command->c_list)
		i = exec_list(command->c_list, omm);
	return (i);
}

int		exec_binary(char **tab, t_omm omm)
{
	int		pid;
	int		ret;
	char	**tabenv;

	ret = 0;
	pid = fork();
	tabenv = NULL;
	if (pid == 0)
		exec_binary_son(omm, tab, tabenv);
	else
	{
		waitpid(pid, &ret, 0);
		if (WIFEXITED(ret))
			ret = WEXITSTATUS(ret);
		else
			ret = 0;
		free(tab);
		if (tabenv)
			free_tab(tabenv);
	}
	return (ret);
}

int		exec_instruction(t_instruction *instruction, t_omm omm)
{
	t_token	*token;
	int		ret;
	char	**tab;

	ret = 0;
	token = instruction->start;
	replace_dollar(token, omm, 0, NULL);
	instruction->start = starize_list(instruction->start, instruction->max,
		get_env(omm.env, "HOME"));
	tab = create_tab(instruction->start, instruction->max);
	if (tab[0] == NULL)
		return (ret);
	if (is_builtin(tab[0]))
	{
		ret = exec_builtin(tab[0], tab, omm.env);
		free(tab);
	}
	else
		ret = exec_binary(tab, omm);
	*(omm.last_ret) = ret;
	return (ret);
}

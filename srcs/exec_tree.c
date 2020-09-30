/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raimbaultbrieuc <marvin@42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 14:45:18 by raimbault         #+#    #+#             */
/*   Updated: 2020/09/25 09:58:14 by braimbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int		exec_andor(t_andor *andor, t_omm omm)
{
	int i;

	i = 0;
	reset_fd(omm);
	if (andor->pipeline)
		i = exec_pipeline(andor->pipeline, omm);
	if (andor->brother)
	{
		if (andor->type == AND_IF && !i)
			i = exec_andor(andor->brother, omm);
		if (andor->type == OR_IF && i)
			i = exec_andor(andor->brother, omm);
	}
	return (i);
}

int		exec_pipeline(t_pipeline *pipeline, t_omm omm)
{
	int i;
	int pfd[2];
	int pid;

	i = 0;
	if (pipeline->brother)
	{
		pipe(pfd);
		pid = fork();
		if (pid == 0)
		{
			close(pfd[1]);
			dup2(pfd[0], 0);
			close(pfd[0]);
			i = exec_pipeline(pipeline->brother, omm);
		}
		else
		{
			close(pfd[0]);
			dup2(pfd[1], 1);
			close(pfd[1]);
			if (pipeline->command)
				i = exec_command(pipeline->command, omm);
			//dup2(omm.stdout, 1);
			//dup2(omm.stdin, 0);
		}
	}
	else
	{
		if (pipeline->command)
			i = exec_command(pipeline->command, omm);
	}
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

int		exec_redirection(t_redirection *redirection, t_omm omm)
{
	int fd;

	if (redirection && redirection->type == GREAT)
	{
		fd = open(redirection->filename, O_CREAT | O_RDWR | O_TRUNC, S_IRWXU);
		if (fd == -1)
		{
			printf("Error : %s\n", strerror(errno));
			return (1);
		}
		dup2(fd, 1);
		close(fd);
	}
	else if (redirection && redirection->type == DGREAT)
	{
		fd = open(redirection->filename, O_CREAT | O_RDWR | O_APPEND);
		if (fd == -1)
		{
			printf("Error : %s\n", strerror(errno));
			return (1);
		}
		dup2(fd, 1);
		close(fd);
	}
	else if (redirection && redirection->type == LESS)
	{
		fd = open(redirection->filename, O_RDONLY);
		if (fd == -1)
		{
			printf("Error : %s\n", strerror(errno));
			return (1);
		}
		dup2(fd, 0);
		close(fd);
	}
	else
	{
		if (omm.stdout != 1)
			dup2(omm.stdout, 1);
		if (omm.stdin != 0)
			dup2(omm.stdin, 0);
	}
	if (redirection && redirection->brother)
	{
		redirection = redirection->brother;
		exec_redirection(redirection, omm);
	}
	return (0);
}

int		exec_instruction(t_instruction *instruction, t_omm omm)
{
	t_token *token;
	int ret;
	char *path;

	ret = 0;;
	char **tab;
	tab = create_tab(instruction->start, instruction->max);
	if (tab[0] == NULL)
		return (ret);
	token = instruction->start;
	int pid = fork();
	if (pid == 0)
	{
		path = get_path(omm.env, token->str);
		if (!path)
			ret = 1;
		else
			ret = execve(path, tab, omm.env);
		printf("%s %s\n", path, tab[0]);
		if (ret)
		{
			free(tab);
			write(2, "Error while executing program\n", 30);
			//exit(0)
		}
		else
			free(tab);
	}
	else
	{
		ft_putstr("");
		wait(&ret);
		free(tab);
	}
	return (ret);
}

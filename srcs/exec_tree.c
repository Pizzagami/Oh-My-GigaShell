/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pizzagami <pizzagami@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 14:45:18 by raimbault         #+#    #+#             */
/*   Updated: 2020/12/21 14:03:30 by braimbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	free_tab(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int		env_size(t_env *first)
{
	int		compteur;
	t_env	*tmp;

	tmp = first;
	compteur = 0;
	while (tmp)
	{
		compteur++;
		tmp = tmp->next;
	}
	return (compteur);
}

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

int		exec_pipeline_father(int pfd[2], t_pipeline *pipeline, t_omm omm,
		int pid)
{
	int x;
	int i;

	i = 0;
	close(pfd[1]);
	dup2(pfd[0], 0);
	close(pfd[0]);
	i = exec_pipeline(pipeline->brother, omm);
	waitpid(pid, &x, 0);
	return (i);
}

int		exec_pipeline_son(int pfd[2], t_pipeline *pipeline, t_omm omm)
{
	close(pfd[0]);
	dup2(pfd[1], 1);
	close(pfd[1]);
	omm.stdout = dup(pfd[1]);
	if (pipeline->command)
		exec_command(pipeline->command, omm);
	exit(0);
	return (1);
}

int		exec_pipeline(t_pipeline *pipeline, t_omm omm)
{
	int		pfd[2];
	int		pid;

	if (pipeline->brother)
	{
		pipe(pfd);
		pid = fork();
		if (pid != 0)
			return (exec_pipeline_father(pfd, pipeline, omm, pid));
		else
			return (exec_pipeline_son(pfd, pipeline, omm));
	}
	else if (pipeline->command)
		return (exec_command(pipeline->command, omm));
	return (0);
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

int		exec_great_redirection(t_redirection *redirection)
{
	int fd;

	fd = open(redirection->filename, O_CREAT | O_RDWR | O_TRUNC, S_IRWXU);
	if (fd == -1)
	{
		perror("bashy");
		return (1);
	}
	dup2(fd, 1);
	close(fd);
	return (0);
}

int		exec_dgreat_redirection(t_redirection *redirection)
{
	int fd;

	fd = open(redirection->filename, O_CREAT | O_RDWR | O_APPEND);
	if (fd == -1)
	{
		printf("Error : %s\n", strerror(errno));
		return (1);
	}
	dup2(fd, 1);
	close(fd);
	return (0);
}

int		exec_less_redirection(t_redirection *redirection)
{
	int fd;

	fd = open(redirection->filename, O_RDONLY);
	if (fd == -1)
	{
		printf("Error : %s\n", strerror(errno));
		return (1);
	}
	dup2(fd, 0);
	close(fd);
	return (0);
}

int		exec_redirection(t_redirection *redirection, t_omm omm)
{
	if (redirection && redirection->type == GREAT
			&& exec_great_redirection(redirection))
		return (1);
	else if (redirection && redirection->type == DGREAT
			&& exec_dgreat_redirection(redirection))
		return (1);
	else if (redirection && redirection->type == LESS
			&& exec_less_redirection(redirection))
		return (1);
	if (redirection && redirection->brother)
	{
		redirection = redirection->brother;
		exec_redirection(redirection, omm);
	}
	return (0);
}

char	**link_tab(t_env *env)
{
	char	**str;
	char	*tmp;
	int		x;
	int		j;

	j = 0;
	x = env_size(env);
	str = (char**)malloc(sizeof(char*) * (x + 1));
	str[x] = NULL;
	while (j < x)
	{
		tmp = ft_strjoin(env->name, "=");
		str[j] = ft_strjoin(tmp, env->val);
		free(tmp);
		env = env->next;
		j++;
	}
	str[j] = NULL;
	return (str);
}

void	check_path_execve(char **tab, t_omm omm, t_token *token, char **tabenv)
{
	char *path;

	path = get_path(omm.env, token->str);
	if (!path)
	{
		ft_putstr("bashy: ");
		ft_putstr(tab[0]);
		ft_putstr(" : command not found\n");
	}
	else
	{
		tabenv = link_tab(omm.env);
		exit(execve(path, tab, tabenv));
	}
	free(tab);
	if (path)
		write(2, "Error while executing program\n", 30);
	exit(127);
}

int		exec_binary(char **tab, t_omm omm, t_token *token)
{
	int		pid;
	int		ret;
	char	**tabenv;

	ret = 0;
	pid = fork();
	tabenv = NULL;
	if (pid == 0)
		check_path_execve(tab, omm, token, tabenv);
	free(tab);
	waitpid(pid, &ret, 0);
	if (WIFEXITED(ret))
		return (WEXITSTATUS(ret));
	return (0);
}

int		exec_instruction(t_instruction *instruction, t_omm omm)
{
	t_token	*token;
	int		ret;
	char	**tab;

	ret = 0;
	token = instruction->start;
	replace_dollar(token, omm);
	instruction->start = starize_list(instruction->start,
			instruction->max, get_env(omm.env, "HOME"));
	tab = create_tab(instruction->start, instruction->max);
	if (tab[0] == NULL)
		return (ret);
	if (is_builtin(tab[0]))
	{
		ret = exec_builtin(tab[0], tab, omm.env);
		free(tab);
	}
	else
		ret = exec_binary(tab, omm, token);
	*(omm.last_ret) = ret;
	return (ret);
}

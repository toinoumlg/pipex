/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 08:36:24 by amalangu          #+#    #+#             */
/*   Updated: 2025/04/22 14:06:05 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	exe_last_child(t_pipex *pipex, char **envp, int *fds)
{
	int		i;
	char	*tmp;

	close(fds[1]);
	dup2(fds[0], STDIN_FILENO);
	close(fds[0]);
	i = -1;
	while (pipex->env[++i])
	{
		tmp = ft_strjoin(pipex->env[i], pipex->childs->command.args[0]);
		execve(tmp, pipex->childs->command.args, envp);
		free(tmp);
	}
	command_nf(pipex->childs->command.args[0]);
	free_pipex(*pipex);
	exit(EXIT_FAILURE);
}

void	exe_first_child(t_pipex *pipex, char **envp, int *fds)
{
	int		i;
	char	*tmp;

	close(fds[0]);
	dup2(fds[1], STDOUT_FILENO);
	close(fds[1]);
	i = -1;
	while (pipex->env[++i])
	{
		tmp = ft_strjoin(pipex->env[i], pipex->childs->command.args[0]);
		execve(tmp, pipex->childs->command.args, envp);
		free(tmp);
	}
	command_nf(pipex->childs->command.args[0]);
	free_pipex(*pipex);
	exit(EXIT_FAILURE);
}

void	first_child(t_pipex *pipex, char **envp)
{
	if (!pipex->in.read && !pipex->in.exist && pipex->childs->command.args)
	{
		pipex->childs->pid = fork();
		if (pipex->childs->pid == 0)
			exe_first_child(pipex, envp, pipex->pipes->fds);
		else
			put_pids_to_array(pipex->childs->pid, pipex->pids);
	}
	handle_errors(pipex->in, pipex->childs);
	close(pipex->pipes->fds[1]);
	free_and_set_to_next_child(&pipex->childs);
}

void	last_child(t_pipex *pipex, char **envp)
{
	if (!pipex->out.write && !pipex->out.exist && pipex->childs->command.args)
	{
		pipex->childs->pid = fork();
		if (pipex->childs->pid == 0)
			exe_last_child(pipex, envp, pipex->pipes->fds);
		else
			put_pids_to_array(pipex->childs->pid, pipex->pids);
	}
	handle_errors(pipex->out, pipex->childs);
	close(pipex->pipes->fds[0]);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 08:36:24 by amalangu          #+#    #+#             */
/*   Updated: 2025/04/24 19:06:54 by amalangu         ###   ########.fr       */
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
	set_out_fd(pipex, pipex->out.path);
	i = -1;
	while (pipex->env[++i])
	{
		tmp = ft_strjoin(pipex->env[i], pipex->children->command.args[0]);
		execve(tmp, pipex->children->command.args, envp);
		free(tmp);
	}
	command_nf(pipex->children->command.args[0]);
	free_pipex(*pipex);
	exit(127);
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
		tmp = ft_strjoin(pipex->env[i], pipex->children->command.args[0]);
		execve(tmp, pipex->children->command.args, envp);
		free(tmp);
	}
	command_nf(pipex->children->command.args[0]);
	free_pipex(*pipex);
	exit(127);
}

void	first_child(t_pipex *pipex, char **envp)
{
	pipe(pipex->pipefds[0]);
	if (!pipex->in.read && !pipex->in.exist && pipex->children->command.args)
	{
		pipex->children->pid = fork();
		if (pipex->children->pid == 0)
			exe_first_child(pipex, envp, pipex->pipefds[0]);
		else
			put_pids_to_array(pipex->children->pid, pipex->pids);
	}
	handle_errors(pipex->in, pipex->children);
	close(pipex->pipefds[0][1]);
	free_and_set_to_next_child(&pipex->children);
}

void	last_child(t_pipex *pipex, char **envp)
{
	if (!pipex->out.write && !pipex->out.exist && pipex->children->command.args)
	{
		pipex->children->pid = fork();
		if (pipex->children->pid == 0)
			exe_last_child(pipex, envp, pipex->pipefds[pipex->size - 2]);
		else
			put_pids_to_array(pipex->children->pid, pipex->pids);
	}
	handle_errors(pipex->out, pipex->children);
	close(pipex->pipefds[pipex->size - 2][0]);
}

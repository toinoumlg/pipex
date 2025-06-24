/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 08:36:24 by amalangu          #+#    #+#             */
/*   Updated: 2025/05/10 17:46:35 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	exe_last_child(t_pipex *pipex, t_cmd *cmd, char **envp, int *fds)
{
	set_fds_last_child(fds, pipex);
	if (pipex->out.is_a_directory >= 0 || pipex->out.write)
	{
		free_pipex(*pipex);
		exit(EXIT_FAILURE);
	}
	if (cmd->access == 0)
		execve(cmd->path, cmd->args, envp);
	handle_cmd_errors(cmd, pipex);
}

void	exe_first_child(t_pipex *pipex, char **envp, int *fds)
{
	set_fds_first_child(fds, pipex);
	if (pipex->cmd->access == 0)
		execve(pipex->cmd->path, pipex->cmd->args, envp);
	handle_cmd_errors(pipex->cmd, pipex);
}

void	first_child(t_pipex *pipex, char **envp)
{
	if (pipe(pipex->pipefds[pipex->i]) == -1)
		pipe_error(pipex);
	if (!pipex->in.read)
	{
		pipex->pids[pipex->i] = fork();
		if (pipex->pids[pipex->i] < 0)
			fork_error(pipex);
		if (pipex->pids[pipex->i] == 0)
			exe_first_child(pipex, envp, pipex->pipefds[pipex->i]);
	}
	close(pipex->pipefds[pipex->i][1]);
	handle_file_errors(pipex->in, pipex->i);
	pipex->i++;
}

void	last_child(t_pipex *pipex, char **envp)
{
	t_cmd	*tmp;

	tmp = get_cmd_i(pipex->cmd, pipex->i);
	pipex->pids[pipex->i] = fork();
	if (pipex->pids[pipex->i] < 0)
		fork_error(pipex);
	if (pipex->pids[pipex->i] == 0)
	{
		if (!pipex->out.write)
			exe_last_child(pipex, tmp, envp, pipex->pipefds[pipex->i - 1]);
		else
			free_pipex(*pipex);
		exit(1);
	}
	close(pipex->pipefds[pipex->i - 1][0]);
	handle_file_errors(pipex->out, pipex->i);
}

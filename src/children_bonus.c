/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:12:40 by amalangu          #+#    #+#             */
/*   Updated: 2025/05/10 17:42:53 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	set_fds_mid_children(t_pipex *pipex, int i)
{
	close(pipex->pipefds[i][0]);
	if (dup2(pipex->pipefds[i - 1][0], STDIN_FILENO) == -1)
		dup2_error(pipex);
	if (dup2(pipex->pipefds[i][1], STDOUT_FILENO) == -1)
		dup2_error(pipex);
	close(pipex->pipefds[i][1]);
	close(pipex->pipefds[i - 1][0]);
}

void	exe_mid_children(t_pipex *pipex, t_cmd *cmd, char **envp)
{
	set_fds_mid_children(pipex, pipex->i);
	if (pipex->cmd->access == 0)
		execve(cmd->path, cmd->args, envp);
	handle_cmd_errors(cmd, pipex);
}

void	mid_children(t_pipex *pipex, char **envp)
{
	while (pipex->i < pipex->size - 1)
	{
		if (pipe(pipex->pipefds[pipex->i]) == -1)
			pipe_error(pipex);
		pipex->pids[pipex->i] = fork();
		if (pipex->pids[pipex->i] < 0)
			fork_error(pipex);
		if (pipex->pids[pipex->i] == 0)
			exe_mid_children(pipex, get_cmd_i(pipex->cmd, pipex->i), envp);
		close(pipex->pipefds[pipex->i][1]);
		close(pipex->pipefds[pipex->i - 1][0]);
		pipex->i++;
	}
}

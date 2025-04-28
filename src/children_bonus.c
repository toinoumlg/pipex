/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:12:40 by amalangu          #+#    #+#             */
/*   Updated: 2025/04/28 14:15:05 by amalangu         ###   ########.fr       */
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

void	exe_mid_children(t_pipex *pipex, char **envp, int i)
{
	set_fds_mid_children(pipex, i);
	try_execve(pipex, envp);
	command_nf(pipex->command->args[0]);
	free_pipex(*pipex);
	exit(127);
}

void	mid_children(t_pipex *pipex, char **envp)
{
	int	i;

	i = 0;
	while (++i < pipex->size - 1)
	{
		if (pipe(pipex->pipefds[i]) == -1)
			pipe_error(pipex);
		if (pipex->command->args)
		{
			pipex->pids[i] = fork();
			if (pipex->pids[i] < 0)
				fork_error(pipex);
			if (pipex->pids[i] == 0)
				exe_mid_children(pipex, envp, i);
		}
		handle_errors_mid(pipex->command);
		close(pipex->pipefds[i][1]);
		close(pipex->pipefds[i - 1][0]);
		free_and_set_to_next_command(&pipex->command);
	}
}

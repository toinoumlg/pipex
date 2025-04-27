/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:12:40 by amalangu          #+#    #+#             */
/*   Updated: 2025/04/27 17:12:58 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	exe_mid_children(t_pipex *pipex, char **envp, int i)
{
	close(pipex->pipefds[i][0]);
	dup2(pipex->pipefds[i - 1][0], STDIN_FILENO);
	dup2(pipex->pipefds[i][1], STDOUT_FILENO);
	close(pipex->pipefds[i][1]);
	close(pipex->pipefds[i - 1][0]);
	try_execve(pipex, envp);
	command_nf(pipex->children->command.args[0]);
	free_pipex(*pipex);
	exit(127);
}

void	mid_children(t_pipex *pipex, char **envp)
{
	int	i;

	i = 0;
	while (++i < pipex->size - 1)
	{
		pipe(pipex->pipefds[i]);
		if (pipex->children->command.args)
		{
			pipex->children->pid = fork();
			if (pipex->children->pid == 0)
				exe_mid_children(pipex, envp, i);
			else
				put_pids_to_array(pipex->children->pid, pipex->pids);
		}
		handle_errors_mid(pipex->children);
		close(pipex->pipefds[i][1]);
		close(pipex->pipefds[i - 1][0]);
		free_and_set_to_next_child(&pipex->children);
	}
}

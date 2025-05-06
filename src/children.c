/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 08:36:24 by amalangu          #+#    #+#             */
/*   Updated: 2025/05/06 13:34:17 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	try_execve(t_pipex *pipex, char **envp)
{
	char	*tmp;
	int		i;

	i = -1;
	while (pipex->env[++i])
	{
		tmp = ft_strjoin(pipex->env[i], pipex->command->args[0]);
		if (!tmp)
			return (free_pipex(*pipex), exit(EXIT_FAILURE));
		execve(tmp, pipex->command->args, envp);
		free(tmp);
	}
}

void	exe_last_child(t_pipex *pipex, char **envp, int *fds)
{
	set_fds_last_child(fds, pipex);
	try_execve(pipex, envp);
	command_nf(pipex->command->args[0]);
	free_pipex(*pipex);
	exit(127);
}

void	exe_first_child(t_pipex *pipex, char **envp, int *fds)
{
	set_fds_first_child(fds, pipex);
	try_execve(pipex, envp);
	command_nf(pipex->command->args[0]);
	free_pipex(*pipex);
	exit(127);
}

void	first_child(t_pipex *pipex, char **envp)
{
	if (pipe(pipex->pipefds[0]) == -1)
		pipe_error(pipex);
	if (!pipex->in.read && pipex->command->args)
	{
		pipex->pids[0] = fork();
		if (pipex->pids[0] < 0)
			fork_error(pipex);
		if (pipex->pids[0] == 0)
			exe_first_child(pipex, envp, pipex->pipefds[0]);
	}
	handle_errors(pipex->in, pipex->command);
	close(pipex->pipefds[0][1]);
	free_and_set_to_next_command(&pipex->command);
}

void	last_child(t_pipex *pipex, char **envp)
{
	if (!pipex->out.write && pipex->command->args)
	{
		pipex->pids[pipex->size - 1] = fork();
		if (pipex->pids[pipex->size - 1] < 0)
			fork_error(pipex);
		if (pipex->pids[pipex->size - 1] == 0)
			exe_last_child(pipex, envp, pipex->pipefds[pipex->size - 2]);
	}
	handle_errors(pipex->out, pipex->command);
	close(pipex->pipefds[pipex->size - 2][0]);
}

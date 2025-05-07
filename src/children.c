/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 08:36:24 by amalangu          #+#    #+#             */
/*   Updated: 2025/05/07 19:35:43 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	try_execve(t_cmd *cmd, char **env, char **envp)
{
	char	*tmp;
	int		i;

	i = -1;
	if (cmd->path)
	{
		execve(cmd->path, cmd->args, envp);
		return ;
	}
	while (env[++i])
	{
		tmp = ft_strjoin(env[i], cmd->args[0]);
		execve(tmp, cmd->args, envp);
		free(tmp);
	}
}

t_cmd	*get_cmd(t_cmd *cmds, int i)
{
	int	j;

	j = i + 1;
	while (--j > 0)
		cmds = cmds->next;
	return (cmds);
}

void	exe_last_child(t_pipex *pipex, char **envp, int *fds)
{
	set_fds_last_child(fds, pipex);
	try_execve(get_cmd(pipex->cmd, pipex->i), pipex->env, envp);
	free_pipex(*pipex);
	exit(127);
}

void	exe_first_child(t_pipex *pipex, char **envp, int *fds)
{
	set_fds_first_child(fds, pipex);
	try_execve(get_cmd(pipex->cmd, pipex->i), pipex->env, envp);
	free_pipex(*pipex);
	exit(127);
}

void	first_child(t_pipex *pipex, char **envp)
{
	if (pipe(pipex->pipefds[pipex->i]) == -1)
		pipe_error(pipex);
	pipex->pids[pipex->i] = fork();
	if (pipex->pids[pipex->i] < 0)
		fork_error(pipex);
	if (pipex->pids[pipex->i] == 0)
		exe_first_child(pipex, envp, pipex->pipefds[pipex->i]);
	if (close(pipex->pipefds[pipex->i][1]) == -1)
		close_error(pipex);
	pipex->i++;
}

void	children(t_pipex *pipex, char **envp)
{
	pipex->pids[pipex->i] = fork();
	if (pipex->pids[pipex->i] < 0)
		fork_error(pipex);
	if (pipex->pids[pipex->i] == 0)
		exe_last_child(pipex, envp, pipex->pipefds[pipex->i - 1]);
	if (close(pipex->pipefds[pipex->i - 1][0]) == -1)
		close_error(pipex);
	pipex->i++;
}

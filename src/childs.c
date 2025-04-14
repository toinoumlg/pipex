/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 08:36:24 by amalangu          #+#    #+#             */
/*   Updated: 2025/04/14 12:49:55 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	exe_child2(t_pipex pipex, char **envp, int *pipefds)
{
	int		i;
	char	*tmp;

	close(pipefds[1]);
	dup2(pipefds[0], STDIN_FILENO);
	close(pipefds[0]);
	i = -1;
	while (pipex.env[++i])
	{
		tmp = ft_strjoin(pipex.env[i], pipex.args[1][0]);
		execve(tmp, pipex.args[1], envp);
		free(tmp);
	}
	command_nf(pipex.args[1][0]);
	free_pipex(pipex);
	exit(EXIT_FAILURE);
}

void	exe_child1(t_pipex pipex, char **envp, int *pipefds)
{
	int		i;
	char	*tmp;

	close(pipefds[0]);
	dup2(pipefds[1], STDOUT_FILENO);
	close(pipefds[1]);
	i = -1;
	while (pipex.env[++i])
	{
		tmp = ft_strjoin(pipex.env[i], pipex.args[0][0]);
		execve(tmp, pipex.args[0], envp);
		free(tmp);
	}
	command_nf(pipex.args[0][0]);
	free_pipex(pipex);
	exit(EXIT_FAILURE);
}

void	child1(t_pipex pipex, char **envp)
{
	int	status;

	if (!pipex.in.read && !pipex.in.exist)
	{
		pipex.childs[0] = fork();
		if (pipex.childs[0] < 0)
			return (perror("Fork:"));
		if (pipex.childs[0] == 0)
			exe_child1(pipex, envp, pipex.pipefds);
		else
			waitpid(pipex.childs[0], &status, 0);
	}
	else if (pipex.in.exist)
		no_file_or_dir(pipex.in.path);
	else if (pipex.in.read)
		permission_denied(pipex.in.path);
	close(pipex.pipefds[1]);
}

void	child2(t_pipex pipex, char **envp)
{
	int status;

	if (!pipex.out.write && !pipex.out.exist)
	{
		pipex.childs[1] = fork();
		if (pipex.childs[1] < 0)
			return (perror("Fork:"));
		if (pipex.childs[1] == 0)
			exe_child2(pipex, envp, pipex.pipefds);
		else
			waitpid(pipex.childs[1], &status, 0);
	}
	else if (pipex.out.exist)
		no_file_or_dir(pipex.out.path);
	else if (pipex.out.write)
		permission_denied(pipex.out.path);
	close(pipex.pipefds[0]);
}
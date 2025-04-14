/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 08:36:24 by amalangu          #+#    #+#             */
/*   Updated: 2025/04/14 09:04:45 by amalangu         ###   ########.fr       */
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
		if (!ft_strnstr(pipex.args[1][0], "/bin/", 5))
			tmp = ft_strjoin(pipex.env[i], pipex.args[1][0]);
		execve(tmp, pipex.args[1], envp);
		free(tmp);
	}
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
}

void	child1(t_pipex pipex, char **envp)
{
	int	status;

	pipex.childs[0] = fork();
	if (pipex.childs[0] < 0)
		return (perror("Fork:"));
	if (pipex.childs[0] == 0)
		return (exe_child1(pipex, envp, pipex.pipefds));
	else
	{
		close(pipex.pipefds[1]);
		waitpid(pipex.childs[0], &status, 0);
	}
}

void	child2(t_pipex pipex, char **envp)
{
	int status;

	pipex.childs[1] = fork();
	if (pipex.childs[1] < 0)
		return (perror("Fork:"));
	if (pipex.childs[1] == 0)
		return (exe_child2(pipex, envp, pipex.pipefds));
	else
	{
		close(pipex.pipefds[0]);
		waitpid(pipex.childs[1], &status, 0);
	}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 18:09:16 by amalangu          #+#    #+#             */
/*   Updated: 2025/04/24 19:57:10 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	end_pipex(t_pipex pipex, int status)
{
	if (pipex.out.write)
		return (free_pipex(pipex), 1);
	free_pipex(pipex);
	return (WEXITSTATUS(status));
}

void	wait_children(int *status, int *pids, int size)
{
	int	i;

	i = -1;
	while (++i < size)
		waitpid(pids[i], status, 0);
}

void	try_execve(t_pipex *pipex, char **envp)
{
	char	*tmp;
	int		i;

	i = -1;
	while (pipex->env[++i])
	{
		tmp = ft_strjoin(pipex->env[i], pipex->children->command.args[0]);
		execve(tmp, pipex->children->command.args, envp);
		free(tmp);
	}
}

void exe_mid_children(t_pipex *pipex, char **envp, int *fds_last, int *fds_next)
{
    close(fds_last[1]);  // Close write end of previous pipe
    close(fds_next[0]);  // Close read end of next pipe
    
    dup2(fds_last[0], STDIN_FILENO);   // Read from previous pipe
    dup2(fds_next[1], STDOUT_FILENO);  // Write to next pipe
    
    close(fds_last[0]);  // Close original file descriptors after duplication
    close(fds_next[1]);
    
    try_execve(pipex, envp);
    command_nf(pipex->children->command.args[0]);
    free_pipex(*pipex);
    exit(127);
}

void	mid_children(t_pipex *pipex, char **envp, int i)
{
	pipe(pipex->pipefds[i]);
	if (pipex->children->command.args)
	{
		pipex->children->pid = fork();
		if (pipex->children->pid == 0)
			exe_mid_children(pipex, envp, pipex->pipefds[i - 1],
				pipex->pipefds[i]);
		else
			put_pids_to_array(pipex->children->pid, pipex->pids);
	}
	handle_errors_mid(pipex->children);
	close(pipex->pipefds[i][0]);
	close(pipex->pipefds[i - 1][1]);
	free_and_set_to_next_child(&pipex->children);
}

void	process_mid_children(t_pipex *pipex, char **envp)
{
	int	i;

	i = 0;
	while (++i < pipex->size - 1)
		mid_children(pipex, envp, i);
}

int	main(int ac, char **av, char **envp)
{
	t_pipex	pipex;
	int		status;

	if (ac < 5)
		return (1);
	pipex.size = init_and_check_args(ac, av, envp, &pipex);
	if (pipex.size < 0)
		return (1);
	first_child(&pipex, envp);
	process_mid_children(&pipex, envp);
	last_child(&pipex, envp);
	wait_children(&status, pipex.pids, pipex.size);
	return (end_pipex(pipex, status));
}

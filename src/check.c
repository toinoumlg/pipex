/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 08:37:28 by amalangu          #+#    #+#             */
/*   Updated: 2025/05/02 18:47:14 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	check_file(char *av, t_file *file)
{
	file->path = av;
	file->exist = access(av, F_OK);
	file->read = access(av, R_OK);
	file->write = access(av, W_OK);
	file->exec = access(av, X_OK);
}

void	set_in_fd(t_pipex *pipex, char *in_path)
{
	if (!pipex->in.read)
	{
		pipex->in.fd = open(in_path, O_RDONLY);
		if (dup2(pipex->in.fd, STDIN_FILENO) == -1)
		{
			close(pipex->in.fd);
			dup2_error(pipex);
		}
		close(pipex->in.fd);
	}
}

void	set_out_fd(t_pipex *pipex, char *out_path)
{
	if (pipex->out.exist || !pipex->out.write)
	{
		unlink(out_path);
		pipex->out.fd = open(out_path, O_CREAT | O_WRONLY, 0666);
		if (pipex->out.fd > 0)
		{
			if (dup2(pipex->out.fd, STDOUT_FILENO) == -1)
			{
				close(pipex->in.fd);
				dup2_error(pipex);
			}
			close(pipex->out.fd);
		}
	}
	check_file(out_path, &pipex->out);
}

void	set_fds(char *in_path, char *out_path, t_pipex *pipex)
{
	check_file(in_path, &pipex->in);
	check_file(out_path, &pipex->out);
	set_in_fd(pipex, pipex->in.path);
	set_out_fd(pipex, pipex->out.path);
}

int	init_and_check_args(int ac, char **av, char **envp, t_pipex *pipex)
{
	pipex->command = NULL;
	pipex->env = NULL;
	pipex->pids = NULL;
	pipex->pipefds = NULL;
	if (!set_env(envp,pipex))
		return (-1);
	set_fds(av[1], av[ac - 1], pipex);
	return (set_cmds(ac, av, pipex));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 21:39:50 by amalangu          #+#    #+#             */
/*   Updated: 2025/04/27 17:10:04 by amalangu         ###   ########.fr       */
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
		dup2(pipex->in.fd, STDIN_FILENO);
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
			dup2(pipex->out.fd, STDOUT_FILENO);
			close(pipex->out.fd);
		}
	}
	check_file(out_path, &pipex->out);
}

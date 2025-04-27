/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children_fds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 17:14:27 by amalangu          #+#    #+#             */
/*   Updated: 2025/04/27 17:32:43 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	set_fds_first_child(int *fds, t_pipex *pipex)
{
	close(fds[0]);
	if (dup2(fds[1], STDOUT_FILENO) == -1)
	{
		perror("dup2");
		free_pipex(*pipex);
		exit(EXIT_FAILURE);
	}
	close(fds[1]);
}

void	set_fds_last_child(int *fds, t_pipex *pipex)
{
	close(fds[1]);
	if (dup2(fds[0], STDIN_FILENO) == -1)
	{
		perror("dup2");
		free_pipex(*pipex);
		exit(EXIT_FAILURE);
	}
	close(fds[0]);
}

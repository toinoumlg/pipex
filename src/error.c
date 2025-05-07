/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 18:39:21 by amalangu          #+#    #+#             */
/*   Updated: 2025/05/07 18:53:04 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	pipe_error(t_pipex *pipex)
{
	perror("pipe");
	free_pipex(*pipex);
	exit(EXIT_FAILURE);
}

void	fork_error(t_pipex *pipex)
{
	perror("fork");
	free_pipex(*pipex);
	exit(EXIT_FAILURE);
}

void	dup2_error(t_pipex *pipex)
{
	perror("dup2");
	free_pipex(*pipex);
	exit(EXIT_FAILURE);
}

void	close_error(t_pipex *pipex)
{
	perror("close");
	free_pipex(*pipex);
	exit(EXIT_FAILURE);
}
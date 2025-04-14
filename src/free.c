/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 08:09:45 by amalangu          #+#    #+#             */
/*   Updated: 2025/04/14 08:24:25 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	free_pipex(t_pipex pipex)
{
	int	i;
	int	j;

	i = -1;
	while (pipex.args[++i])
	{
		j = -1;
		while (pipex.args[i][++j])
			free(pipex.args[i][j]);
		free(pipex.args[i]);
	}
	if (pipex.args)
		free(pipex.args);
	i = -1;
	while (pipex.env[++i])
		free(pipex.env[i]);
	if (pipex.env)
		free(pipex.env);
}

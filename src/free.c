/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 08:09:45 by amalangu          #+#    #+#             */
/*   Updated: 2025/04/14 15:11:53 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	free_pipex(t_pipex pipex)
{
	int	i;
	int	j;

	i = -1;
	while (++i < 1)
	{
		j = -1;
		if (pipex.childs[i].command.args)
		{
			while (pipex.childs[i].command.args[++j])
				free(pipex.childs[i].command.args[++j]);
			free(pipex.childs[i].command.args);
		}
	}
	i = -1;
	while (pipex.env[++i])
		free(pipex.env[i]);
	if (pipex.env)
		free(pipex.env);
}

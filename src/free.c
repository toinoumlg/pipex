/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 08:09:45 by amalangu          #+#    #+#             */
/*   Updated: 2025/05/10 16:59:09 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	free_args(char **args)
{
	int	i;

	i = -1;
	if (args)
	{
		while (args[++i])
			free(args[i]);
		free(args);
	}
	args = NULL;
}

void	free_all_cmds(t_cmd *cmd)
{
	t_cmd	*tmp;

	while (cmd)
	{
		tmp = cmd->next;
		if (cmd->path)
			free(cmd->path);
		if (cmd->args)
			free_args(cmd->args);
		free(cmd);
		cmd = tmp;
	}
}

void	free_pipex(t_pipex pipex)
{
	if (pipex.cmd)
		free_all_cmds(pipex.cmd);
	if (pipex.env)
		free_args(pipex.env);
	if (pipex.pipefds)
		free(pipex.pipefds);
	if (pipex.pids)
		free(pipex.pids);
}

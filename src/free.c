/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 08:09:45 by amalangu          #+#    #+#             */
/*   Updated: 2025/05/05 17:22:00 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	free_args(char **args)
{
	int	i;

	i = -1;
	while (args[++i])
		free(args[i]);
	free(args);
	args = NULL;
}

void	free_and_set_to_next_command(t_command **cmd)
{
	t_command	*next;
	t_command	*tmp;

	if (!*cmd)
		return ;
	tmp = *cmd;
	if (!tmp->next)
		return ;
	next = tmp->next;
	if (tmp->args)
		free_args(tmp->args);
	if (tmp->path)
		free(tmp->path);
	free(tmp);
	*cmd = next;
}

void	free_all_commands(t_command *cmd)
{
	t_command	*tmp;

	while (cmd)
	{
		tmp = cmd->next;
		if (cmd->args)
			free_args(cmd->args);
		if (cmd->path)
			free(cmd->path);
		free(cmd);
		cmd = tmp;
	}
}

void	free_pipex(t_pipex pipex)
{
	if (pipex.command)
		free_all_commands(pipex.command);
	if (pipex.env)
		free_args(pipex.env);
	if (pipex.pipefds)
		free(pipex.pipefds);
	if (pipex.pids)
		free(pipex.pids);
}

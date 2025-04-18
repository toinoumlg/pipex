/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 08:09:45 by amalangu          #+#    #+#             */
/*   Updated: 2025/04/19 17:29:25 by amalangu         ###   ########.fr       */
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

void	free_and_set_to_next_child(t_child **childs)
{
	t_child	*next;
	t_child	*tmp;

	if (!*childs)
		return ;
	tmp = *childs;
	if (!tmp->next)
		return ;
	next = tmp->next;
	if (tmp->command.args)
		free_args(tmp->command.args);
	if (tmp->command.path)
		free(tmp->command.path);
	free(tmp);
	*childs = next;
}

void	free_and_set_to_next_pipes(t_pipes **pipes)
{
	t_pipes	*next;
	t_pipes	*tmp;

	if (!*pipes)
		return ;
	tmp = *pipes;
	if (!tmp->next)
		return ;
	next = tmp->next;
	free(tmp);
	*pipes = next;
}

void	free_all_childs(t_child *childs)
{
	t_child	*tmp;

	while (childs)
	{
		tmp = childs->next;
		if (childs->command.args)
			free_args(childs->command.args);
		if (childs->command.path)
			free(childs->command.path);
		free(childs);
		childs = tmp;
	}
}

void	free_all_pipes(t_pipes *pipes)
{
	t_pipes	*tmp;

	while (pipes)
	{
		tmp = pipes->next;
		free(pipes);
		pipes = tmp;
	}
}

void	free_pipex(t_pipex pipex)
{
	free_all_childs(pipex.childs);
	free_args(pipex.env);
	free_all_pipes(pipex.pipes);
	free(pipex.pids);
}

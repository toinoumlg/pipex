/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 08:09:45 by amalangu          #+#    #+#             */
/*   Updated: 2025/04/24 19:17:01 by amalangu         ###   ########.fr       */
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

void	free_and_set_to_next_child(t_child **children)
{
	t_child	*next;
	t_child	*tmp;

	if (!*children)
		return ;
	tmp = *children;
	if (!tmp->next)
		return ;
	next = tmp->next;
	if (tmp->command.args)
		free_args(tmp->command.args);
	if (tmp->command.path)
		free(tmp->command.path);
	free(tmp);
	*children = next;
}

void	free_all_children(t_child *children)
{
	t_child	*tmp;

	while (children)
	{
		tmp = children->next;
		if (children->command.args)
			free_args(children->command.args);
		if (children->command.path)
			free(children->command.path);
		free(children);
		children = tmp;
	}
}

// void	free_all_pipes(t_pipes *pipes)
// {
// 	t_pipes	*tmp;

// 	while (pipes)
// 	{
// 		tmp = pipes->next;
// 		free(pipes);
// 		pipes = tmp;
// 	}
// }

void	free_pipex(t_pipex pipex)
{
	free_all_children(pipex.children);
	free_args(pipex.env);
	free(pipex.pids);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 08:09:45 by amalangu          #+#    #+#             */
/*   Updated: 2025/04/14 18:09:10 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	free_and_set_to_next(t_child **childs)
{
	int		i;
	t_child	*next;
	t_child	*tmp;

	if (!*childs)
		return ;
	tmp = *childs;
	next = tmp->next;
	i = -1;
	if (tmp->command.args)
	{
		while (tmp->command.args[++i])
			free(tmp->command.args[i]);
		free(tmp->command.args);
	}
	if (tmp->command.path)
		free(tmp->command.path);
	free(tmp);
	*childs = next;
}

void	free_all_childs(t_child *childs)
{
	t_child	*tmp;
	int		i;

	while (childs)
	{
		tmp = childs->next;
		i = -1;
		if (childs->command.args)
		{
			while (childs->command.args[++i])
				free(childs->command.args[i]);
			free(childs->command.args);
		}
		if (childs->command.path)
			free(childs->command.path);
		free(childs);
		childs = tmp;
	}
}

void	free_env(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
		free(env[i]);
	free(env);
}

void	free_pipex(t_pipex pipex)
{
	free_all_childs(pipex.childs);
	free_env(pipex.env);
}

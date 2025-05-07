/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:32:53 by amalangu          #+#    #+#             */
/*   Updated: 2025/05/07 19:27:16 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	set_up_cat(t_cmd **cmd, char **args, t_cmd *tmp)
{
	free(args);
	tmp->args = ft_calloc(sizeof(char *), 2);
	if (!tmp->args)
	{
		free(tmp);
		*cmd = NULL;
		return (-1);
	}
	tmp->args[0] = ft_strdup("cat");
	return (0);
}

int	set_new_command(t_cmd **cmd, char **args)
{
	t_cmd	*tmp;

	tmp = *cmd;
	tmp = ft_calloc(sizeof(t_cmd), 1);
	if (!tmp)
	{
		*cmd = NULL;
		return (-1);
	}
	tmp->next = NULL;
	if (args[0] != NULL)
		tmp->args = args;
	else if (args[0] == NULL && set_up_cat(cmd, args, tmp))
		return (-1);
	*cmd = tmp;
	return (0);
}

int	add_new_command(t_cmd **cmd, char **args)
{
	t_cmd	*tmp;
	t_cmd	*head;

	tmp = *cmd;
	if (!tmp)
	{
		if (set_new_command(&tmp, args))
			return (-1);
		*cmd = tmp;
	}
	else
	{
		head = tmp;
		while (tmp->next)
			tmp = tmp->next;
		if (set_new_command(&tmp->next, args))
			return (-1);
		*cmd = head;
	}
	return (0);
}

int	check_for_program_path(t_cmd *cmd)
{
	while (cmd)
	{
		cmd->path = NULL;
		if (ft_strchr(cmd->args[0], '/'))
		{
			if (!access(cmd->args[0], X_OK))
				cmd->path = cmd->args[0];
			else
			{
				cmd->path = ft_strdup(cmd->args[0]);
				if (!cmd->path)
					return (-1);
				free_args(cmd->args);
				cmd->args = NULL;
			}
		}
		cmd = cmd->next;
	}
	return (0);
}

int	set_cmds(int ac, char **av, t_pipex *pipex)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (++i < ac - 1 && ++j)
		if (add_new_command(&pipex->cmd, ft_split(av[i], ' ')))
			return (-1);
	if (check_for_program_path(pipex->cmd))
		return (-1);
	pipex->pids = ft_calloc(sizeof(int), j + 1);
	if (!pipex->pids)
		return (-1);
	pipex->pipefds = ft_calloc(sizeof(int[2]), j);
	if (!pipex->pipefds)
		return (-1);
	return (j);
}

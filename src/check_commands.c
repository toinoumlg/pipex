/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:32:53 by amalangu          #+#    #+#             */
/*   Updated: 2025/05/05 18:29:01 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	set_new_command(t_command **cmd, char **args)
{
	t_command	*tmp;

	tmp = *cmd;
	tmp = ft_calloc(sizeof(t_command), 1);
	if (!tmp)
		return (free_args(args), -1);
	tmp->next = NULL;
	if (args[0] != NULL)
		tmp->args = args;
	else
	{
		free(args);
		tmp->args = ft_calloc(sizeof(char *), 2);
		if (!tmp->args)
			return (free(tmp), *cmd = NULL, -1);
		tmp->args[0] = ft_strdup("cat");
		if (!tmp->args[0])
			return (free(tmp->args), free(tmp), -1);
	}
	*cmd = tmp;
	return (0);
}

int	add_new_command(t_command **cmd, char **args)
{
	t_command	*tmp;
	t_command	*head;

	tmp = *cmd;
	if (!args)
		return (-1);
	if (!tmp)
	{
		if (set_new_command(&tmp, args))
			return (-1);
		*cmd = tmp;
		return (0);
	}
	else
	{
		head = tmp;
		while (tmp->next)
			tmp = tmp->next;
		if (set_new_command(&tmp->next, args))
			return (-1);
		*cmd = head;
		return (0);
	}
}

int	check_for_program_path(t_command *cmd)
{
	char	*tmp;

	while (cmd)
	{
		cmd->path = NULL;
		if (ft_strchr(cmd->args[0], '/'))
		{
			if (!access(cmd->args[0], X_OK))
			{
				tmp = ft_strdup(ft_strrchr(cmd->args[0], '/') + 1);
				if (!tmp)
					return (-1);
				cmd->path = cmd->args[0];
				cmd->args[0] = tmp;
			}
			else
			{
				cmd->path = ft_strdup(cmd->args[0]);
				free_args(cmd->args);
				cmd->args = NULL;
				if (!cmd->path)
					return (-1);
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
		if (add_new_command(&pipex->command, ft_split(av[i], ' ')))
			return (free_pipex(*pipex), -1);
	if (check_for_program_path(pipex->command))
		return (free_pipex(*pipex), -1);
	pipex->pids = ft_calloc(sizeof(int), j + 1);
	pipex->pipefds = ft_calloc(sizeof(int[2]), j);
	if (!pipex->pids || !pipex->pipefds)
		return (free_pipex(*pipex), -1);
	return (j);
}

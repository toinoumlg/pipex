/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmds.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:32:53 by amalangu          #+#    #+#             */
/*   Updated: 2025/05/08 16:09:26 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

t_cmd	*get_cmd_i(t_cmd *cmd, int i)
{
	int	j;

	j = i + 1;
	while (--j > 0)
		cmd = cmd->next;
	return (cmd);
}

int	set_new_cmd(t_cmd **cmd, char **args, char **env)
{
	t_cmd	*tmp;

	tmp = ft_calloc(sizeof(t_cmd), 1);
	if (!tmp)
		return (-1);
	tmp->next = NULL;
	tmp->args = args;
	if (try_access(tmp->args, env, &tmp->path, &tmp->access))
		return (free(tmp), -1);
	*cmd = tmp;
	return (0);
}

int	add_new_cmd(t_cmd **cmd, char **args, char **env)
{
	t_cmd	*tmp;
	t_cmd	*head;

	tmp = *cmd;
	if (!args)
		return (-1);
	if (!tmp)
	{
		if (set_new_cmd(&tmp, args, env))
			return (free_args(args), -1);
		*cmd = tmp;
		return (0);
	}
	else
	{
		head = tmp;
		while (tmp->next)
			tmp = tmp->next;
		if (set_new_cmd(&tmp->next, args, env))
			return (free_args(args), -1);
		*cmd = head;
		return (0);
	}
}

int	set_cmds(int ac, char **av, t_pipex *pipex)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (++i < ac - 1 && ++j)
		if (add_new_cmd(&pipex->cmd, ft_split(av[i], ' '), pipex->env))
			return (free_pipex(*pipex), -1);
	pipex->pids = ft_calloc(sizeof(int), j + 1);
	pipex->pipefds = ft_calloc(sizeof(int [2]), j);
	if (!pipex->pids || !pipex->pipefds)
		return (free_pipex(*pipex), -1);
	return (j);
}

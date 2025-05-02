/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:32:53 by amalangu          #+#    #+#             */
/*   Updated: 2025/05/02 14:47:58 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	set_new_command(t_command **cmd, char **args)
{
	t_command	*tmp;

	tmp = *cmd;
	tmp = ft_calloc(sizeof(t_command), 1);
	tmp->next = NULL;
	if (args[0] != NULL)
		tmp->args = args;
	else
	{
		free(args);
		tmp->args = ft_calloc(sizeof(char *), 2);
		tmp->args[0] = ft_strdup("cat");
	}
	*cmd = tmp;
}

void	add_new_command(t_command **cmd, char **args)
{
	t_command	*tmp;
	t_command	*head;

	tmp = *cmd;
	if (!tmp)
	{
		set_new_command(&tmp, args);
		*cmd = tmp;
		return ;
	}
	else
	{
		head = tmp;
		while (tmp->next)
			tmp = tmp->next;
		set_new_command(&tmp->next, args);
		*cmd = head;
	}
}

void	check_for_program_path(t_command *cmd)
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
				cmd->path = cmd->args[0];
				cmd->args[0] = tmp;
			}
			else
			{
				cmd->path = ft_strdup(cmd->args[0]);
				free_args(cmd->args);
				cmd->args = NULL;
			}
		}
		cmd = cmd->next;
	}
}

int	set_cmds(int ac, char **av, t_pipex *pipex)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	pipex->command = NULL;
	while (++i < ac - 1 && ++j)
		add_new_command(&pipex->command, ft_split(av[i], ' '));
	check_for_program_path(pipex->command);
	pipex->pids = ft_calloc(sizeof(int), j + 1);
	pipex->pipefds = ft_calloc(sizeof(int [2]), j);
	return (j);
}

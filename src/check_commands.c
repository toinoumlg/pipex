/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:32:53 by amalangu          #+#    #+#             */
/*   Updated: 2025/04/27 17:11:43 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	set_new_child(t_child **child, char **args)
{
	t_child	*tmp;

	tmp = *child;
	tmp = ft_calloc(sizeof(t_child), 1);
	tmp->next = NULL;
	if (args[0] != NULL)
		tmp->command.args = args;
	else
	{
		free(args);
		tmp->command.args = ft_calloc(sizeof(char *), 2);
		tmp->command.args[0] = ft_calloc(sizeof(char), 4);
		tmp->command.args[0][0] = 'c';
		tmp->command.args[0][1] = 'a';
		tmp->command.args[0][2] = 't';
	}
	*child = tmp;
}

void	add_new_child(t_child **child, char **args)
{
	t_child	*tmp;
	t_child	*head;

	tmp = *child;
	if (!tmp)
	{
		set_new_child(&tmp, args);
		*child = tmp;
		return ;
	}
	else
	{
		head = tmp;
		while (tmp->next)
			tmp = tmp->next;
		set_new_child(&tmp->next, args);
		*child = head;
	}
}

void	check_for_program_path(t_child *children)
{
	char	*tmp;

	while (children)
	{
		children->command.path = NULL;
		if (ft_strchr(children->command.args[0], '/'))
		{
			if (!access(children->command.args[0], X_OK))
			{
				tmp = ft_strdup(ft_strrchr(children->command.args[0], '/') + 1);
				children->command.path = children->command.args[0];
				children->command.args[0] = tmp;
			}
			else
			{
				children->command.path = ft_strdup(children->command.args[0]);
				free_args(children->command.args);
				children->command.args = NULL;
			}
		}
		children = children->next;
	}
}

int	set_cmds(int ac, char **av, t_pipex *pipex)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	pipex->children = NULL;
	while (++i < ac - 1 && ++j)
		add_new_child(&pipex->children, ft_split(av[i], ' '));
	check_for_program_path(pipex->children);
	pipex->pids = ft_calloc(sizeof(int), j + 1);
	pipex->pipefds = ft_calloc(sizeof(int [2]), j);
	return (j);
}

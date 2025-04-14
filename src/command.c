/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:32:53 by amalangu          #+#    #+#             */
/*   Updated: 2025/04/14 17:06:28 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	set_new_child(t_child **child, char **args)
{
	t_child	*tmp;

	tmp = *child;
	tmp = ft_calloc(sizeof(t_child), 1);
	tmp->next = NULL;
	tmp->command.args = args;
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

void	check_for_program_path(t_child *childs)
{
	int		j;
	char	*tmp;

	while (childs)
	{
		{
			if (ft_strchr(childs->command.args[0], '/'))
			{
				if (!access(childs->command.args[0], X_OK))
				{
					tmp = ft_strdup(ft_strrchr(childs->command.args[0], '/')
							+ 1);
					childs->command.path = childs->command.args[0];
					childs->command.args[0] = tmp;
				}
				else
				{
					no_file_or_dir(childs->command.args[0]);
					j = -1;
					while (childs->command.args[++j])
						free(childs->command.args[j]);
					free(childs->command.args);
					childs->command.args = NULL;
					childs->command.path = NULL;
				}
			}
			else
				childs->command.path = NULL;
		}
		childs = childs->next;
	}
}

void	set_cmds(int ac, char **av, t_pipex *pipex)
{
	int	i;

	i = 1;
	pipex->childs = NULL;
	while (++i < ac - 1)
		add_new_child(&pipex->childs, ft_split(av[i], ' '));
	check_for_program_path(pipex->childs);
}

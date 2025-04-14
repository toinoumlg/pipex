/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 21:52:55 by amalangu          #+#    #+#             */
/*   Updated: 2025/04/14 21:59:50 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	set_new_pipe(t_pipes **pipes)
{
	t_pipes	*tmp;

	tmp = *pipes;
	tmp = ft_calloc(sizeof(t_pipes), 1);
	pipe(tmp->fds);
	tmp->next = NULL;
	*pipes = tmp;
}

void	add_new_pipe(t_pipes **pipes)
{
	t_pipes	*tmp;
	t_pipes	*head;

	tmp = *pipes;
	if (!tmp)
	{
		set_new_pipe(&tmp);
		*pipes = tmp;
		return ;
	}
	else
	{
		head = tmp;
		while (tmp->next)
			tmp = tmp->next;
		set_new_pipe(&tmp->next);
		*pipes = head;
	}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children_fds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 17:14:27 by amalangu          #+#    #+#             */
/*   Updated: 2025/04/27 17:16:12 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	set_fds_first_child(int *fds)
{
	close(fds[0]);
	dup2(fds[1], STDOUT_FILENO);
	close(fds[1]);
}

void	set_fds_last_child(int *fds)
{
	close(fds[1]);
	dup2(fds[0], STDIN_FILENO);
	close(fds[0]);
}

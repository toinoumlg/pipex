/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 18:09:16 by amalangu          #+#    #+#             */
/*   Updated: 2025/05/02 14:33:16 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	end_pipex(t_pipex pipex, int status)
{
	if (pipex.out.write)
		return (free_pipex(pipex), 1);
	free_pipex(pipex);
	return (WEXITSTATUS(status));
}

void	wait_children(int *status, int *pids, int size)
{
	int	i;

	i = -1;
	while (++i < size)
		waitpid(pids[i], status, 0);
}

int	main(int ac, char **av, char **envp)
{
	t_pipex	pipex;
	int		status;

	if (ac < 5)
		return (1);
	pipex.size = init_and_check_args(ac, av, envp, &pipex);
	if (pipex.size < 0)
		return (1);
	first_child(&pipex, envp);
	mid_children(&pipex, envp);
	last_child(&pipex, envp);
	wait_children(&status, pipex.pids, pipex.size);
	return (end_pipex(pipex, status));
}

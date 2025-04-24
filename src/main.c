/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 18:09:16 by amalangu          #+#    #+#             */
/*   Updated: 2025/04/24 18:24:15 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	main(int ac, char **av, char **envp)
{
	t_pipex	pipex;
	int		status;

	if (ac != 5)
		return (1);
	if (init_and_check_args(ac, av, envp, &pipex))
		return (1);
	first_child(&pipex, envp);
	last_child(&pipex, envp);
	waitpid(pipex.pids[0], &status, 0);
	waitpid(pipex.pids[1], &status, 0);
	if (pipex.out.write)
		return (free_pipex(pipex), 1);
	free_pipex(pipex);
	return (WEXITSTATUS(status));
}

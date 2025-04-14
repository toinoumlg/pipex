/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 18:09:16 by amalangu          #+#    #+#             */
/*   Updated: 2025/04/14 10:33:42 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	main(int ac, char **av, char **envp)
{
	t_pipex	pipex;

	if (init_and_check_args(ac, av, envp, &pipex))
		return (free_pipex(pipex), -1);
	if (pipe(pipex.pipefds))
		return (ft_printf("pipe error\n"), -1);
	child1(pipex, envp);
	child2(pipex, envp);
	free_pipex(pipex);
	return (0);
}

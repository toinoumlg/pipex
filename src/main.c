/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 18:09:16 by amalangu          #+#    #+#             */
/*   Updated: 2025/04/14 18:40:01 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	main(int ac, char **av, char **envp)
{
	t_pipex	pipex;

	if (init_and_check_args(ac, av, envp, &pipex))
		return (-1);
	pipe(pipex.pipefds);
	first_child(&pipex, envp);
	// while (pipex.childs->next)
	// 	mid_childs(pipex, envp, &pipex.childs);
	last_child(&pipex, envp);
	free_pipex(pipex);
	return (0);
}

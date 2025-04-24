/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 08:37:28 by amalangu          #+#    #+#             */
/*   Updated: 2025/04/24 18:24:02 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	put_pids_to_array(int pid, int *pids)
{
	int	i;

	i = 0;
	while (pids[i] != 0)
		i++;
	pids[i] = pid;
}

void	set_fds(char *in_path, char *out_path, t_pipex *pipex)
{
	check_file(in_path, &pipex->in);
	check_file(out_path, &pipex->out);
	set_in_fd(pipex, in_path);
	set_out_fd(pipex, out_path);
}

int	init_and_check_args(int ac, char **av, char **envp, t_pipex *pipex)
{
	pipex->env = set_env(envp);
	if (!pipex->env)
		return (-1);
	set_fds(av[1], av[ac - 1], pipex);
	set_cmds(ac, av, pipex);
	return (0);
}

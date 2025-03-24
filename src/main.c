/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 18:09:16 by amalangu          #+#    #+#             */
/*   Updated: 2025/03/24 18:55:21 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

char	**set_env(char **envp)
{
	char	**env;
	int		i;

	i = -1;
	env = ft_split(ft_strchr(envp[4], '/'), ':');
	if (!env)
		return (NULL);
	while (env[i++])
		env[i] = ft_strjoin(env[i], "/");
	return (env);
}

int	open_fds(int ac, char **av, t_pipex *pipex)
{
	pipex->f1 = open(av[1], O_RDWR);
	pipex->f2 = open(av[ac - 1], O_RDWR);
	if (pipex->f1 < 0 && pipex->f2 < 0)
		return (-1);
	else if (pipex->f1 < 0)
		return (close(pipex->f2), -1);
	else if (pipex->f2 < 0)
		return (close(pipex->f1), -1);
	else
		return (0);
}

int	set_args(int ac, char **av, t_pipex *pipex)
{
	
}

int	set_args(int ac, char **av, t_pipex *pipex)
{
	if (ac < 2)
		return (-1);
	if (open_fds(ac, av, pipex))
		return (-1);
	if (set_cmds(ac, av, pipex))
}

int	check_args(int ac, char **av, char **envp, t_pipex *pipex)
{
	pipex->env = set_env(envp);
	if (set_args(ac, av, pipex))
		return (-1);
	ft_printf("%s\n", pipex->env[0]);
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	t_pipex pipex;
	if (check_args(ac, av, envp, &pipex))
		return (-1);
}
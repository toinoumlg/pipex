/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 08:37:28 by amalangu          #+#    #+#             */
/*   Updated: 2025/04/14 09:04:07 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

char	*get_path(char **envp)
{
	int	i;

	i = -1;
	while (envp[++i])
		if (ft_strnstr(envp[i], "PATH", 5))
			return (ft_strchr(envp[i], '/'));
	return (NULL);
}

char	**set_env(char **envp)
{
	char	**env;
	char	*tmp;
	int		i;

	i = -1;
	env = ft_split(get_path(envp), ':');
	if (!env)
		return (NULL);
	while (env[++i])
	{
		tmp = env[i];
		env[i] = ft_strjoin(tmp, "/");
		free(tmp);
	}
	return (env);
}

int	check_fds(char *in, char *out)
{
	if (access(in, R_OK) == 0 && access(out, W_OK) == 0)
		return (0);
	else
		return (-1);
}

int	open_fds(int ac, char **av, t_pipex *pipex)
{
	check_fds(av[1], av[ac - 1]);
	pipex->in = open(av[1], O_RDONLY);
	pipex->out = open(av[ac - 1], O_WRONLY);
	dup2(pipex->in, STDIN_FILENO);
	close(pipex->in);
	dup2(pipex->out, STDOUT_FILENO);
	close(pipex->out);
	return (0);
}

int	set_cmds(int ac, char **av, t_pipex *pipex)
{
	int	i;

	i = 1;
	pipex->args = ft_calloc(sizeof(char **), ac - 2);
	while (++i < ac - 1)
		pipex->args[i - 2] = ft_split(av[i], ' ');
	return (0);
}

int	set_args(int ac, char **av, t_pipex *pipex)
{
	if (ac < 2)
		return (-1);
	if (open_fds(ac, av, pipex))
		return (-1);
	if (set_cmds(ac, av, pipex))
		return (-1);
	return (0);
}

int	init_and_check_args(int ac, char **av, char **envp, t_pipex *pipex)
{
	pipex->env = set_env(envp);
	if (!pipex->env)
		return (-1);
	if (set_args(ac, av, pipex))
		return (-1);
	return (0);
}
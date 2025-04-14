/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 08:37:28 by amalangu          #+#    #+#             */
/*   Updated: 2025/04/14 20:50:42 by amalangu         ###   ########.fr       */
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

void	check_file(char *av, t_file *file)
{
	file->path = av;
	file->exist = access(av, F_OK);
	file->read = access(av, R_OK);
	file->write = access(av, W_OK);
	file->exec = access(av, X_OK);
}

void	open_fds(int ac, char **av, t_pipex *pipex)
{
	check_file(av[1], &pipex->in);
	check_file(av[ac - 1], &pipex->out);
	if (!pipex->in.read)
	{
		pipex->in.fd = open(av[1], O_RDONLY);
		dup2(pipex->in.fd, STDIN_FILENO);
		close(pipex->in.fd);
	}
	if (pipex->out.exist)
	{
		pipex->out.fd = open(av[ac - 1], O_CREAT | O_WRONLY, 0666);
		if (pipex->out.fd > 0)
		{
			dup2(pipex->out.fd, STDOUT_FILENO);
			close(pipex->out.fd);
		}
		return (check_file(av[ac - 1], &pipex->out));
	}
	if (!pipex->out.write)
	{
		pipex->out.fd = open(av[ac - 1], O_WRONLY);
		dup2(pipex->out.fd, STDOUT_FILENO);
		close(pipex->out.fd);
	}
}

int	init_and_check_args(int ac, char **av, char **envp, t_pipex *pipex)
{
	if (ac < 5)
		return (-1);
	pipex->env = set_env(envp);
	if (!pipex->env)
		return (-1);
	open_fds(ac, av, pipex);
	set_cmds(ac, av, pipex);
	return (0);
}

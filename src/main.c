/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 18:09:16 by amalangu          #+#    #+#             */
/*   Updated: 2025/03/26 20:29:36 by amalangu         ###   ########.fr       */
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
	if (check_fds(av[1], av[ac - 1]))
		return (-1);
	pipex->in = open(av[1], O_RDONLY);
	pipex->out = open(av[ac - 1], O_WRONLY);
	dup2(pipex->in, 0);
	dup2(pipex->out, 1);
	close(pipex->in);
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

int	check_args(int ac, char **av, char **envp, t_pipex *pipex)
{
	pipex->env = set_env(envp);
	if (set_args(ac, av, pipex))
		return (-1);
	return (0);
}

void	free_pipex(t_pipex *pipex)
{
	int	i;
	int	j;

	i = -1;
	while (pipex->args[++i])
	{
		j = -1;
		while (pipex->args[i][++j])
			free(pipex->args[i][j]);
		free(pipex->args[i]);
	}
	free(pipex->args);
	i = -1;
	while (pipex->env[++i])
		free(pipex->env[i]);
	free(pipex->env);
	free(pipex);
}

void	exe_parent(t_pipex pipex, char **envp, int *pipefds)
{
	int		i;
	char	*tmp;

	dup2(pipefds[1], 1);
	close(pipefds[0]);
	i = -1;
	tmp = ft_strjoin(pipex.env[++i], pipex.args[1][0]);
	while (execve(tmp, pipex.args[1], envp) < 0)
	{
		free(tmp);
		tmp = ft_strjoin(pipex.env[++i], pipex.args[1][0]);
	}
}

void	exe_child(t_pipex pipex, char **envp, int *pipefds)
{
	int		i;
	char	*tmp;

	dup2(pipefds[0], 0);
	close(pipefds[1]);
	i = -1;
	while (pipex.env[++i])
	{
		tmp = ft_strjoin(pipex.env[i], pipex.args[0][0]);
		if (execve(tmp, pipex.args[0], envp) == 0)
			return (free(tmp));
		free(tmp);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_pipex pipex;
	pid_t child;
	int pipefds[2];
	if (check_args(ac, av, envp, &pipex))
		return (-1);
	if (pipe(pipefds))
		return (ft_printf("pipe error\n"), -1);
	child = fork();
	if (child < 0)
		return (perror("Fork:"), -1);
	if (child == 0)
		exe_child(pipex, envp, pipefds);
	child2 = fork();
		exe_child2(pipex, envp, pipefds);
	free_pipex(&pipex);
}
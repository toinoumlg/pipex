/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 21:39:50 by amalangu          #+#    #+#             */
/*   Updated: 2025/05/05 17:59:46 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

char	**get_env(char **envp)
{
	int	i;

	i = -1;
	while (envp[++i])
		if (ft_strnstr(envp[i], "PATH", 5))
			return (ft_split(ft_strchr(envp[i], '/'), ':'));
	return (NULL);
}

int	set_env(char **envp, t_pipex *pipex)
{
	char	**env;
	int		i;
	int		size;

	size = 0;
	i = -1;
	pipex->env = ft_calloc(sizeof(char *), 15);
	if (!envp || !pipex->env)
		return (free_args(pipex->env), -1);
	env = get_env(envp);
	if (!env)
		return (free_args(pipex->env), -1);
	while (env[++i])
	{
		pipex->env[i] = ft_strjoin(env[i], "/");
		if (!pipex->env[i])
			return (free_args(env), free_args(pipex->env), -1);
	}
	free_args(env);
	return (0);
}

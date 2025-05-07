/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 21:39:50 by amalangu          #+#    #+#             */
/*   Updated: 2025/05/07 11:33:29 by amalangu         ###   ########.fr       */
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
	char	*tmp;
	char	**env;
	int		i;

	i = -1;
	if (!envp)
		return (-1);
	pipex->env = ft_calloc(sizeof(char *), 100);
	env = get_env(envp);
	if (!env)
		return (-1);
	while (env[++i])
	{
		tmp = ft_strdup(env[i]);
		pipex->env[i] = ft_strjoin(tmp, "/");
		free(tmp);
		if (!pipex->env[i])
			return (free_args(env), -1);
	}
	free_args(env);
	return (0);
}

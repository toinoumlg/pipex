/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 21:39:50 by amalangu          #+#    #+#             */
/*   Updated: 2025/05/02 19:02:04 by amalangu         ###   ########.fr       */
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
	int		i;

	i = -1;
	if (!envp)
		return (-1);
	pipex->env = get_env(envp);
	if (!pipex->env)
		return (-1);
	while (pipex->env[++i])
	{
		tmp = pipex->env[i];
		pipex->env[i] = ft_strjoin(tmp, "/");
		free(tmp);
		if (!pipex->env[i])
			return (-1);
	}
	return (0);
}

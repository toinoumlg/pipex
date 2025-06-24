/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_access.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 16:48:50 by amalangu          #+#    #+#             */
/*   Updated: 2025/05/10 17:37:51 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	check_for_program_path(char **args, char **path)
{
	if (ft_strchr(args[0], '/'))
	{
		*path = ft_strdup(args[0]);
		if (!path)
			return (-1);
		return (0);
	}
	else
		return (1);
}

void	try_access_with_path(char *path, int *acs_i)
{
	int	i;

	i = -1;
	if (access(path, F_OK) == 0)
	{
		if (access(path, X_OK) == 0)
			*acs_i = 0;
		else
			*acs_i = 1;
	}
	else
		*acs_i = -1;
	return ;
}

int	try_x_rights(char *tmp, char **path, int *acs_i)
{
	if (access(tmp, X_OK) == 0)
	{
		*path = tmp;
		*acs_i = 0;
		return (0);
	}
	else
	{
		*acs_i = 1;
		free(tmp);
		return (0);
	}
}

int	try_access_with_env(char **env, char **args, char **path, int *acs_i)
{
	char	*tmp;
	int		i;

	i = -1;
	while (env[++i])
	{
		tmp = ft_strjoin(env[i], args[0]);
		if (!tmp)
			return (-1);
		if (access(tmp, F_OK) == 0)
			return (try_x_rights(tmp, path, acs_i));
		else
			free(tmp);
	}
	*acs_i = -1;
	return (0);
}

int	try_access(char **args, char **env, char **path, int *acs_i)
{
	if (check_for_program_path(args, path) == -1)
		return (-1);
	if (*path)
		return (try_access_with_path(*path, acs_i), 0);
	else
		return (try_access_with_env(env, args, path, acs_i));
}

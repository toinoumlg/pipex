/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putstr_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 11:24:13 by amalangu          #+#    #+#             */
/*   Updated: 2025/04/24 17:23:35 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	permission_denied(char *path)
{
	ft_putstr_fd("pipex: permission denied: ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd("\n", 2);
}

void	no_file_or_dir(char *path)
{
	ft_putstr_fd("pipex: no such file or directory: ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd("\n", 2);
}

void	command_nf(char *cmd)
{
	ft_putstr_fd("pipex: command not found: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd("\n", 2);
}

void	handle_errors(t_file file, t_child *child)
{
	if (file.exist)
		no_file_or_dir(file.path);
	else if (file.read)
		permission_denied(file.path);
	else if (!child->command.args && child->command.path)
		no_file_or_dir(child->command.path);
}

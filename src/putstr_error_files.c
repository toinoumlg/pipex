/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putstr_error_files.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 11:24:13 by amalangu          #+#    #+#             */
/*   Updated: 2025/05/10 17:21:52 by amalangu         ###   ########.fr       */
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

void	is_a_directory(char *path)
{
	ft_putstr_fd("pipex: is a directory: ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd("\n", 2);
}

void	handle_file_errors(t_file file, int i)
{
	if (file.exist)
		return (no_file_or_dir(file.path));
	else if (file.write && i >= 1)
		return (permission_denied(file.path));
	else if (file.read)
		return (permission_denied(file.path));
	else if (file.is_a_directory > 0 && i != 0)
		return (is_a_directory(file.path));
}

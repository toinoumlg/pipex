/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putstr_error_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 15:31:21 by amalangu          #+#    #+#             */
/*   Updated: 2025/05/10 16:19:55 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	cmd_nf(char *cmd)
{
	ft_putstr_fd("pipex: command not found: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd("\n", 2);
}

void	handle_cmd_errors(t_cmd *cmd, t_pipex *pipex)
{
	if (cmd->access == 1)
	{
		permission_denied(cmd->args[0]);
		free_pipex(*pipex);
		exit(NO_X_RIGHTS);
	}
	if (cmd->access == -1)
	{
		cmd_nf(cmd->args[0]);
		free_pipex(*pipex);
		exit(COMMAND_NF);
	}
	if (cmd->access == 0)
	{
		free_pipex(*pipex);
		exit(EXIT_FAILURE);
	}
}

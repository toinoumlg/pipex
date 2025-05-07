/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:27:42 by amalangu          #+#    #+#             */
/*   Updated: 2025/05/07 17:45:01 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	print_cmds(t_cmd *cmds)
{
	while (cmds)
	{
		ft_putstr_fd(cmds->args[0], 2);
		cmds = cmds->next;
	}
}

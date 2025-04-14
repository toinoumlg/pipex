/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:27:42 by amalangu          #+#    #+#             */
/*   Updated: 2025/04/14 21:59:19 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	print_childs(t_child *childs)
{
	while (childs)
	{
		ft_putstr_fd(childs->command.args[0], 2);
		childs = childs->next;
	}
}

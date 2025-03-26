/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 20:16:32 by amalangu          #+#    #+#             */
/*   Updated: 2025/03/26 20:16:45 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libftprintf/include/libftprintf.h"
# include <fcntl.h>

typedef struct s_pipex
{
	char	**env;
	char	***args;
	int		*pipefds;
	int		in;
	int		out;

}			t_pipex;

#endif
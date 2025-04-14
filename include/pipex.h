/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 20:16:32 by amalangu          #+#    #+#             */
/*   Updated: 2025/04/14 10:14:11 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libftprintf/include/libftprintf.h"
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef struct s_file
{
	int		fd;
	int		exist;
	int		read;
	int		write;
	int		exec;
}			t_file;

typedef struct s_pipex
{
	char	**env;
	char	***args;
	int		pipefds[2];
	pid_t	childs[2];
	t_file	in;
	t_file	out;

}			t_pipex;

int			init_and_check_args(int ac, char **av, char **envp, t_pipex *pipex);
void		child1(t_pipex pipex, char **envp);
void		child2(t_pipex pipex, char **envp);
void		free_pipex(t_pipex pipex);

#endif
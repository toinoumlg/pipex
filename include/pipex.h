/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 20:16:32 by amalangu          #+#    #+#             */
/*   Updated: 2025/04/14 18:33:26 by amalangu         ###   ########.fr       */
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
	char				*path;
	int					fd;
	int					exist;
	int					read;
	int					write;
	int					exec;
}						t_file;

typedef struct s_command
{
	char				*path;
	char				**args;
}						t_command;

typedef struct s_child
{
	pid_t				pid;
	t_command			command;
	struct s_child		*next;
}						t_child;

typedef struct s_pipefds
{
	int					pipefds[2];
	struct s_pipefds	*next;

}						t_pipefds;

typedef struct s_pipex
{
	char				**env;
	t_pipefds			pipes;
	int					pipefds[2];
	t_child				*childs;
	t_file				in;
	t_file				out;

}						t_pipex;

int						init_and_check_args(int ac, char **av, char **envp,
							t_pipex *pipex);
void					first_child(t_pipex *pipex, char **envp);
void					last_child(t_pipex *pipex, char **envp);
void					free_pipex(t_pipex pipex);
void					free_and_set_to_next(t_child **childs);
void					command_nf(char *cmd);
void					no_file_or_dir(char *path);
void					permission_denied(char *path);
void					set_cmds(int ac, char **av, t_pipex *pipex);

void					print_childs(t_child *childs);
#endif
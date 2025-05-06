/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 20:16:32 by amalangu          #+#    #+#             */
/*   Updated: 2025/05/06 13:57:21 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libftprintf/include/libftprintf.h"
# include <errno.h>
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
	struct s_command	*next;

}						t_command;

typedef struct s_pipex
{
	char				**env;
	int					(*pipefds)[2];
	t_command			*command;
	int					*pids;
	int					size;
	t_file				in;
	t_file				out;
}						t_pipex;

int						init_and_check_args(int ac, char **av, char **envp,
							t_pipex *pipex);
int						set_env(char **envp, t_pipex *pipex);
int						set_cmds(int ac, char **av, t_pipex *pipex);
void					first_child(t_pipex *pipex, char **envp);
void					mid_children(t_pipex *pipex, char **envp);
void					last_child(t_pipex *pipex, char **envp);
void					set_fds_first_child(int *fds, t_pipex *pipex);
void					set_fds_last_child(int *fds, t_pipex *pipex);
void					try_execve(t_pipex *pipex, char **envp);
void					command_nf(char *cmd);
void					no_file_or_dir(char *path);
void					permission_denied(char *path);
void					handle_errors(t_file file, t_command *cmd);
void					handle_errors_mid(t_command *cmd);
void					pipe_error(t_pipex *pipex);
void					fork_error(t_pipex *pipex);
void					dup2_error(t_pipex *pipex);
void					free_pipex(t_pipex pipex);
void					free_args(char **args);
void					free_and_set_to_next_command(t_command **cmd);

#endif
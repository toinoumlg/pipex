/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 20:16:32 by amalangu          #+#    #+#             */
/*   Updated: 2025/05/10 17:55:48 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libftprintf/include/libftprintf.h"
# include <errno.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>

# define NO_X_RIGHTS 126
# define COMMAND_NF 127

typedef struct s_file
{
	char			*path;
	int				is_a_directory;
	int				fd;
	int				exist;
	int				read;
	int				write;
	int				exec;
}					t_file;

typedef struct s_cmd
{
	char			*path;
	char			**args;
	int				access;
	int				is_a_path;
	struct s_cmd	*next;

}					t_cmd;

typedef struct s_pipex
{
	char			**env;
	int				(*pipefds)[2];
	t_cmd			*cmd;
	int				*pids;
	int				size;
	int				i;
	t_file			in;
	t_file			out;
}					t_pipex;

int					init_and_check_args(int ac, char **av, char **envp,
						t_pipex *pipex);
int					set_env(char **envp, t_pipex *pipex);
int					set_cmds(int ac, char **av, t_pipex *pipex);
void				first_child(t_pipex *pipex, char **envp);
void				mid_children(t_pipex *pipex, char **envp);
void				last_child(t_pipex *pipex, char **envp);
void				set_fds_first_child(int *fds, t_pipex *pipex);
void				set_fds_last_child(int *fds, t_pipex *pipex);
void				try_execve(t_pipex *pipex, char **envp);
void				cmd_nf(char *cmd);
void				no_file_or_dir(char *path);
void				permission_denied(char *path);
int					try_access(char **args, char **env, char **path,
						int *acs_i);
void				handle_file_errors(t_file file, int i);
void				handle_cmd_errors(t_cmd *cmd, t_pipex *pipex);
void				pipe_error(t_pipex *pipex);
void				fork_error(t_pipex *pipex);
void				dup2_error(t_pipex *pipex);
void				close_error(t_pipex *pipex);
t_cmd				*get_cmd_i(t_cmd *cmd, int i);

void				free_pipex(t_pipex pipex);
void				free_args(char **args);
void				free_and_set_to_next_cmd(t_cmd **cmd);

#endif
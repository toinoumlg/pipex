/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 20:16:32 by amalangu          #+#    #+#             */
/*   Updated: 2025/04/24 19:41:32 by amalangu         ###   ########.fr       */
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
	char			*path;
	int				fd;
	int				exist;
	int				read;
	int				write;
	int				exec;
}					t_file;

typedef struct s_command
{
	char			*path;
	char			**args;
}					t_command;

typedef struct s_child
{
	pid_t			pid;
	t_command		command;
	struct s_child	*next;
}					t_child;

typedef struct s_pipex
{
	char			**env;
	int (*pipefds)[2];
	t_child			*children;
	int				*pids;
	int				size;
	t_file			in;
	t_file			out;

}					t_pipex;

int					init_and_check_args(int ac, char **av, char **envp,
						t_pipex *pipex);
char				**set_env(char **envp);
void				check_file(char *av, t_file *file);
void				set_in_fd(t_pipex *pipex, char *in_path);
void				set_out_fd(t_pipex *pipex, char *out_path);
void				first_child(t_pipex *pipex, char **envp);
void				last_child(t_pipex *pipex, char **envp);
void				free_pipex(t_pipex pipex);
void				free_args(char **args);
void				free_and_set_to_next_child(t_child **children);
void				command_nf(char *cmd);
void				no_file_or_dir(char *path);
void				permission_denied(char *path);
int					set_cmds(int ac, char **av, t_pipex *pipex);
void				handle_errors(t_file file, t_child *child);
void				handle_errors_mid(t_child *child);
void				put_pids_to_array(int pid, int *pids);
void				print_children(t_child *children);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 22:34:15 by michoi            #+#    #+#             */
/*   Updated: 2025/06/11 16:45:20 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"
# include <sys/wait.h>

typedef struct s_cmd		t_cmd;
typedef struct s_env		t_env;
typedef struct s_env_pack	t_env_pack;

typedef struct s_pipe
{
	int						pipe_fd[2];
	int						prev_fd;
}							t_pipe;

typedef struct s_child_process
{
	char					*path;
	char					**args;
}							t_cp;

int							execution(t_cmd *cmd_args, t_env_pack *env);

// ─── ⋆⋅☆⋅⋆ ── utils ─── ⋆⋅☆⋅⋆ ──

pid_t						init_child_process(void);
int							init_pipe(int pipe_fd[2]);
int							duplicate_fd(int file_fd, int old_fd);
int							duplicate_files(t_cmd *cmd_arg);
int							close_fd(int fd);
int							open_files(t_cmd *cmd_list);
int							close_files(t_cmd *cmd);
void						print_path_err(t_cmd *cmd);
int							redirect_pipe(t_cmd cmd, t_pipe cmd_pipe);

// ─── ⋆⋅☆⋅⋆ ── cmd path ─── ⋆⋅☆⋅⋆ ──

char						**get_env_arr(t_env *env);
char						*get_cmd_path(t_env *env, char *cmd);

// ─── ⋆⋅☆⋅⋆ ── execution ─── ⋆⋅☆⋅⋆ ──
int							run_single_cmd(const char **builtins, t_cmd *cmd,
								t_env *env);
int							run_command(t_cp *cp, char **env_arr);
void						exec_external_cmd(t_cmd *cmd, t_env *env);

// ─── ⋆⋅☆⋅⋆ ── wait && exit ─── ⋆⋅☆⋅⋆ ──
int							wait_for_pid(pid_t pid, int *stat);
int							handle_exit_status(int wait_stat);
int							wait_and_set_exit_status(pid_t last_pid);
int							set_path_exit_code(int err_no);

#endif

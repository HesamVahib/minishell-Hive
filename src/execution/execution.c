/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 22:01:29 by michoi            #+#    #+#             */
/*   Updated: 2025/06/14 16:37:05 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execution.h"

static int	redirect_pipe(t_cmd *cmd, t_pipe *cmd_pipe)
{
	int	status;

	status = SUCCESS;
	if (cmd_pipe->prev_fd != -1)
	{
		if (duplicate_fd(cmd_pipe->prev_fd, STDIN_FILENO))
			status = FAILURE;
	}
	if (cmd->is_piped)
	{
		if (duplicate_fd(cmd_pipe->pipe_fd[1], STDOUT_FILENO))
			status = FAILURE;
	}
	if (cmd_pipe->pipe_fd[0] != cmd_pipe->prev_fd)
	{
		if (close_fd(cmd_pipe->pipe_fd[0]))
			status = FAILURE;
	}
	return (status);
}

static int	cleanup_fds_from_parent(t_cmd *cmd, t_pipe cmd_pipe)
{
	if (!cmd)
		return (FAILURE);
	if (cmd_pipe.prev_fd >= 0)
		close_fd(cmd_pipe.prev_fd);
	if (cmd->is_piped)
		close_fd(cmd_pipe.pipe_fd[1]);
	close_files(cmd);
	return (SUCCESS);
}

static void	run_cmd_in_child(t_env *env, t_cmd *cmd, t_pipe *cmd_pipe,
		const char **builtins)
{
	int	exit_stat_builtin;
	int	argv_i;

	signal(SIGQUIT, SIG_DFL);
	if (redirect_pipe(cmd, cmd_pipe))
	{
		ft_putendl_fd("pipe redirection failed", STDERR_FILENO);
		cleanup_exit(env, cmd);
		exit(EXIT_FAILURE);
	}
	argv_i = check_valid_argv(cmd->argv);
	if (cmd->argv && is_in_array(builtins, cmd->argv[argv_i]))
	{
		open_dup_files(cmd, env);
		exit_stat_builtin = exec_builtin(env, cmd);
		cleanup_exit(env, cmd);
		exit(exit_stat_builtin & 255);
	}
	execute_external_cmd(cmd, env);
}

int	run_multiple_cmd(t_cmd *cmd, t_env *env, const char **builtins)
{
	t_pipe	cmd_pipe;
	pid_t	child_pid;
	pid_t	last_pid;

	last_pid = -1;
	ft_memset(&cmd_pipe, -1, sizeof(t_pipe));
	while (cmd)
	{
		if (cmd->is_piped && init_pipe(cmd_pipe.pipe_fd))
			return (FAILURE);
		child_pid = init_child_process();
		if (child_pid == -1)
			return (FAILURE);
		if (!cmd->next)
			last_pid = child_pid;
		if (child_pid == 0)
			run_cmd_in_child(env, cmd, &cmd_pipe, builtins);
		cleanup_fds_from_parent(cmd, cmd_pipe);
		cmd_pipe.prev_fd = cmd_pipe.pipe_fd[0];
		cmd = cmd->next;
	}
	if (wait_and_set_exit_status(last_pid))
		return (FAILURE);
	return (SUCCESS);
}

int	execution(t_cmd *cmd_args, t_env_pack *env_pack)
{
	t_env		*env;
	const char	*builtins[] = {CMD_CD, CMD_ECHO, CMD_ENV, CMD_EXPORT, CMD_EXIT,
		CMD_PWD, CMD_UNSET, NULL};

	env = env_pack->mshell_env;
	cleanup_env(env_pack->sys_envlist);
	env_pack->sys_envlist = NULL;
	if (!cmd_args->next)
		return (run_single_cmd(builtins, cmd_args, env));
	if (run_multiple_cmd(cmd_args, env, builtins))
		return (FAILURE);
	return (SUCCESS);
}

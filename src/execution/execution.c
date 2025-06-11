/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 22:01:29 by michoi            #+#    #+#             */
/*   Updated: 2025/06/11 18:58:15 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execution.h"

int	redirect_pipe(t_cmd cmd, t_pipe cmd_pipe)
{
	int status;

	status = SUCCESS;
	if (cmd_pipe.prev_fd != -1)
	{
		if (duplicate_fd(cmd_pipe.prev_fd, STDIN_FILENO))
			status = FAILURE;
	}
	if (cmd.is_piped)
	{
		if (duplicate_fd(cmd_pipe.pipe_fd[1], STDOUT_FILENO))
			status = FAILURE;
	}
	if (cmd_pipe.pipe_fd[0] != cmd_pipe.prev_fd)
	{
		if (close_fd(cmd_pipe.pipe_fd[0]))
			status = FAILURE;
	}
	return (status);
}

int	cleanup_fds_from_parent(t_cmd *cmd, t_pipe cmd_pipe)
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

int	execution(t_cmd *cmd_args, t_env_pack *env_pack)
{
	t_env *env = env_pack->mshell_env;
	cleanup_env(env_pack->sys_envlist);
	env_pack->sys_envlist = NULL;

	int argv_i = 0;
	while (!ft_strcmp(cmd_args->argv[argv_i], ""))
		argv_i++;
	
	printf("argv_i: %d\n", argv_i);
	const char	*builtins[] = {CMD_CD, CMD_ECHO, CMD_ENV, CMD_EXPORT, CMD_EXIT,
			CMD_PWD, CMD_UNSET, NULL};
	t_pipe		cmd_pipe;
	pid_t		child_pid;
	pid_t		last_pid;
	t_cmd *head;
	
	head = cmd_args;
	last_pid = -1; // PLEASE TAKE CARE THIS NUMBER
	if (!cmd_args->next)
		return (run_single_cmd(builtins, cmd_args, env));
	ft_memset(&cmd_pipe, -1, sizeof(t_pipe));
	while (cmd_args)
	{
		// if (cmd_args->error)
		// {
		// 	cmd_args = cmd_args->next;
		// 	continue ;
		// }
		// init pipe
		if (cmd_args->is_piped)
		{
			if (init_pipe(cmd_pipe.pipe_fd))
				return (FAILURE);
		}
		child_pid = init_child_process();
		if (child_pid == -1)
			return (FAILURE);
		if (!cmd_args->next)
			last_pid = child_pid;
		if (child_pid == 0)
		{
			signal(SIGQUIT, SIG_DFL);
			if (redirect_pipe(*cmd_args, cmd_pipe))
				exit(EXIT_FAILURE);
			if (cmd_args->argv && is_in_array(builtins, cmd_args->argv[0]))
			{
				// cleanup
				if (open_files(cmd_args))
					exit(FAILURE);
				if (duplicate_files(cmd_args))
					exit(FAILURE);
				int exit_builtin = exec_builtin(env, cmd_args);
				exit_run(env);
				cleanup_env(env);
				free_cmd_list(cmd_args);
				exit(exit_builtin);
			}
			exec_external_cmd(cmd_args, env);
		}
		cleanup_fds_from_parent(cmd_args, cmd_pipe);
		cmd_pipe.prev_fd = cmd_pipe.pipe_fd[0];
		cmd_args = cmd_args->next;
	}
	wait_and_set_exit_status(last_pid);
	return (SUCCESS);
}
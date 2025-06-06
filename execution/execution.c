/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvahib <hvahib@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 22:01:29 by michoi            #+#    #+#             */
/*   Updated: 2025/06/01 23:55:05 by hvahib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execution.h"

// temp
void	print_arr(char **arr)
{
	while (*arr)
	{
		printf("%s\n", *arr);
		arr++;
	}
}

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

int	execution(t_cmd *cmd_args, t_env *env)
{
	const char	*builtins[] = {CMD_CD, CMD_ECHO, CMD_ENV, CMD_EXPORT, CMD_EXIT,
			CMD_PWD, CMD_UNSET, NULL};
	t_pipe		cmd_pipe;
	pid_t		child_pid;
	pid_t		last_pid;
	
	last_pid = -1; // PLEASE TAKE CARE THIS NUMBER
	// single cmd
	if (!cmd_args->next)
		return (run_single_cmd(builtins, cmd_args, env));
	ft_memset(&cmd_pipe, -1, sizeof(t_pipe));
	// multiple cmds
	while (cmd_args)
	{
		if (cmd_args->error)
		{
			cmd_args = cmd_args->next;
			continue ;
		}
		// init pipe
		if (cmd_args->is_piped)
		{
			if (init_pipe(cmd_pipe.pipe_fd))
				return (FAILURE);
		}
		// fork
		child_pid = init_child_process();
		if (child_pid == -1)
			return (FAILURE);
		if (!cmd_args->next)
			last_pid = child_pid;
		if (child_pid == 0)
		{
			if (redirect_pipe(*cmd_args, cmd_pipe))
				exit(EXIT_FAILURE);
			if (is_in_array(builtins, cmd_args->argv[0]))
			{
				// cleanup
				if (open_files(cmd_args))
					exit(FAILURE);
				if (duplicate_files(cmd_args))
					exit(FAILURE);
				exit(exec_builtin(env, cmd_args->argv[0], cmd_args->argv + 1));
				// return (FAILURE);
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

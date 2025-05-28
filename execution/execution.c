/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 22:01:29 by michoi            #+#    #+#             */
/*   Updated: 2025/05/28 14:58:50 by michoi           ###   ########.fr       */
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

int	handle_exit_status(int wait_stat)
{
	int	last_exit_stat;

	last_exit_stat = WEXITSTATUS(wait_stat);
	if (WIFEXITED(wait_stat))
	{
		// printf("last exit stat: %d\n", last_exit_stat);
		// set_and_get_exit_status(last_exit_stat, true);
		return (last_exit_stat);
	}
	return (-1);
}

void	run_command(t_cp *cp, char **env_arr)
{
	if (execve(cp->path, cp->args, env_arr))
	{
		free(cp->path);
		free_array(&env_arr);
		perror("execve failed");
		exit(EXIT_FAILURE);
		// close file?
	}
}

int	execute_single_cmd(const char **builtins, t_cmd *cmd, t_env *env)
{
	pid_t	child_pid;
	int		wait_stat;

	if (is_in_array(builtins, cmd->argv[0]))
	{
		if (open_files(cmd))
			return (FAILURE);
		if (duplicate_files(cmd))
			return (FAILURE);
		return (exec_builtin(env, cmd->argv[0], cmd->argv + 1));
	}
	else
	{
		child_pid = init_child_process();
		if (child_pid == -1)
			return (FAILURE);
		if (child_pid == 0)
			exec_external_cmd(cmd, env);
		if (close_files(cmd))
			return (FAILURE);
		if (waitpid(child_pid, &wait_stat, 0) == -1)
			return (FAILURE);
		return (handle_exit_status(wait_stat));
	}
	return (SUCCESS);
}

static int	close_fddd(int fd, char *file, int line)
{
	if (close(fd))
	{
		// perror("close failed");
		fprintf(stderr, "close failed: %s: %s[%i]\n", strerror(errno), file,
			line);
		return (FAILURE);
	}
	return (SUCCESS);
}

#define close_fd(x) close_fddd(x, __FILE__, __LINE__)

int	execution(t_cmd *cmd_args, t_env *env)
{
	const char	*builtins[] = {CMD_CD, CMD_ECHO, CMD_ENV, CMD_EXPORT, CMD_EXIT,
			CMD_PWD, CMD_UNSET, NULL};
	t_pipe		cmd_pipe;
	pid_t		child_pid;
	int			wait_stat;

	// int			last_exit_stat;
	// single cmd
	if (!cmd_args->next)
	{
		if (cmd_args->error)
			return (FAILURE);
		set_and_get_exit_status(execute_single_cmd(builtins, cmd_args, env),
			true);
		return (SUCCESS);
	}
	// multiple cmds
	ft_memset(&cmd_pipe, -1, sizeof(t_pipe));
	// cmd_pipe = (t_pipe){.prev_fd = -1, .pipe_fd[0] = -1, .pipe_fd[1] = -1};
	while (cmd_args)
	{
		// when there's error while executing a command, it moves on the next command
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
		if (child_pid == 0)
		{
			fprintf(stderr,
					"cmd: %s, pipe read end: %d, pipe write end: %d,"
					"prev fd: %d\n",
					cmd_args->argv[0],
					cmd_pipe.pipe_fd[0],
					cmd_pipe.pipe_fd[1],
					cmd_pipe.prev_fd);
			if (cmd_pipe.prev_fd != -1)
			{
				duplicate_fd(cmd_pipe.prev_fd, STDIN_FILENO);
				close_fd(cmd_pipe.prev_fd);
			}
			if (cmd_args->is_piped)
			{
				duplicate_fd(cmd_pipe.pipe_fd[1], STDOUT_FILENO);
				close_fd(cmd_pipe.pipe_fd[1]);
			}
			if (cmd_pipe.pipe_fd[0] != cmd_pipe.prev_fd)
				close_fd(cmd_pipe.pipe_fd[0]);
			if (is_in_array(builtins, cmd_args->argv[0]))
			{
				if (open_files(cmd_args))
					return (FAILURE);
				if (duplicate_files(cmd_args))
					return (FAILURE);
				exit(exec_builtin(env, cmd_args->argv[0], cmd_args->argv + 1));
				// return (FAILURE);
			}
			exec_external_cmd(cmd_args, env);
		}
		if (cmd_pipe.prev_fd != -1)
			close_fd(cmd_pipe.prev_fd);
		if (cmd_args->is_piped)
			close_fd(cmd_pipe.pipe_fd[1]);
		cmd_pipe.prev_fd = cmd_pipe.pipe_fd[0];
		close_files(cmd_args);
		cmd_args = cmd_args->next;
	}
	// if (waitpid(child_pid, &wait_stat, 0) == -1)
	// 	return (FAILURE);
	while (wait(&wait_stat) > 0)
		;
	set_and_get_exit_status(handle_exit_status(wait_stat), true);
	// close_fd(cmd_pipe.prev_fd);
	return (SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 22:01:29 by michoi            #+#    #+#             */
/*   Updated: 2025/05/17 22:57:40 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execution.h"

void	print_arr(char **arr)
{
	while (*arr)
	{
		printf("%s\n", *arr);
		arr++;
	}
}

int	close_fd(int fd)
{
	if (close(fd))
	{
		perror("close failed");
		return (FAILURE);
	}
	return (SUCCESS);
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

int	execution(t_cmd *cmd_args, t_env *env)
{
	const char	*builtins[] = {CMD_CD, CMD_ECHO, CMD_ENV, CMD_EXPORT, CMD_PWD,
			CMD_UNSET, NULL};
	t_pipe		cmd_pipe;
	pid_t		child_pid;
	int			wait_stat;

	// if there's only one cmd (no pipe)
	if (!cmd_args->next)
	{
		if (is_in_array(builtins, cmd_args->argv[0]))
		{
			if (duplicate_files(cmd_args))
				return (FAILURE);
			if (exec_builtin(env, cmd_args->argv[0], cmd_args->argv + 1))
				return (FAILURE);
		}
		else
		{
			// fork
			child_pid = init_child_process();
			if (child_pid == -1)
				return (FAILURE);
			if (child_pid == 0)
				exec_external_cmd(cmd_args, env);
			if (waitpid(child_pid, &wait_stat, 0) == -1)
				return (FAILURE);
			printf("exit stat: %d\n", wait_stat);
		}
		// !!!!exit stat code!!!!
		return (SUCCESS);
	}
	// multiple cmds
	ft_bzero(&cmd_pipe, sizeof(t_pipe));
	while (cmd_args)
	{
		// init pipe
		if (init_pipe(cmd_pipe.pipe_fd))
			return (FAILURE);
		// fork
		child_pid = init_child_process();
		// if (child_pid == -1)
		// 	return (FAILURE);
		if (child_pid == 0)
		{
			// redirection
			// dup
			// execute

			duplicate_fd(cmd_pipe.prev_fd, STDIN_FILENO);
			close_fd(cmd_pipe.prev_fd);
			if (cmd_args->next)
			{
				duplicate_fd(cmd_pipe.pipe_fd[1], STDOUT_FILENO);
				close_fd(cmd_pipe.pipe_fd[1]);
			}
			if (duplicate_files(cmd_args))
				return (FAILURE);
			close_fd(cmd_pipe.pipe_fd[0]);
			exec_external_cmd(cmd_args, env);
		}
		else
		{
			close_fd(cmd_pipe.pipe_fd[1]);
			cmd_pipe.prev_fd = cmd_pipe.pipe_fd[0];
			if (waitpid(child_pid, &wait_stat, 0) == -1)
				return (FAILURE);
			cmd_args = cmd_args->next;
		}
	}
	return (SUCCESS);
}

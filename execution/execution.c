/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 22:01:29 by michoi            #+#    #+#             */
/*   Updated: 2025/05/24 20:25:26 by michoi           ###   ########.fr       */
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
		// Do i really need to open infiles here?!
		if (duplicate_files(cmd))
			return (FAILURE);
		if (exec_builtin(env, cmd->argv[0], cmd->argv + 1))
			return (FAILURE);
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
	}
	// !!!!exit stat code!!!!
	return (SUCCESS);
}

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
		if (execute_single_cmd(builtins, cmd_args, env))
			return (FAILURE);
		// // !!!!exit stat code!!!!
		return (SUCCESS);
	}
	// multiple cmds
	ft_bzero(&cmd_pipe, sizeof(t_pipe));
	cmd_pipe.prev_fd = -1;
	while (cmd_args)
	{
		if (cmd_args->error)
		{
			cmd_args = cmd_args->next;
			continue ;
		}
		// init pipe
		if (init_pipe(cmd_pipe.pipe_fd))
			return (FAILURE);
		// fork
		child_pid = init_child_process();
		if (child_pid == -1)
			return (FAILURE);
		if (child_pid == 0)
		{
			if (cmd_pipe.prev_fd != -1)
			{
				duplicate_fd(cmd_pipe.prev_fd, STDIN_FILENO);
				close_fd(cmd_pipe.prev_fd);
			}
			if (cmd_args->next)
			{
				duplicate_fd(cmd_pipe.pipe_fd[1], STDOUT_FILENO);
				close_fd(cmd_pipe.pipe_fd[1]);
			}
			close_fd(cmd_pipe.pipe_fd[0]);
			exec_external_cmd(cmd_args, env);
		}
		close_fd(cmd_pipe.pipe_fd[1]);
		if (cmd_pipe.prev_fd != -1)
			close_fd(cmd_pipe.prev_fd);
		cmd_pipe.prev_fd = cmd_pipe.pipe_fd[0];
		close_files(cmd_args);
		cmd_args = cmd_args->next;
	}
	// if (waitpid(child_pid, &wait_stat, 0) == -1)
	// 	return (FAILURE);
	while (wait(&wait_stat) > 0)
		;
	close_fd(cmd_pipe.prev_fd);
	return (SUCCESS);
}

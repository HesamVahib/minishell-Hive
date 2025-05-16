/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvahib <hvahib@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 22:01:29 by michoi            #+#    #+#             */
/*   Updated: 2025/05/16 15:38:10 by hvahib           ###   ########.fr       */
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

pid_t	init_child_process(void)
{
	pid_t	cp;

	cp = fork();
	if (cp == -1)
	{
		perror("Fork failed");
		return (errno);
	}
	return (cp);
}

int	close_file(int file_fd)
{
	if (close(file_fd))
	{
		perror("close failed");
		return (FAILURE);
	}
	return (SUCCESS);
}

int	duplicate_fd(int file_fd, int old_fd)
{
	if (dup2(file_fd, old_fd) == -1)
	{
		perror("dup2 failed");
		return (FAILURE);
	}
	return (SUCCESS);
}

int	duplicate_files(t_cmd *cmd_arg)
{
	if (cmd_arg->infile_fd > -1)
	{
		if (duplicate_fd(cmd_arg->infile_fd, STDIN_FILENO))
			return (FAILURE);
		if (close_file(cmd_arg->infile_fd))
			return (FAILURE);
	}
	if (cmd_arg->outfile_fd > -1)
	{
		if (duplicate_fd(cmd_arg->outfile_fd, STDOUT_FILENO))
			return (FAILURE);
		if (close_file(cmd_arg->outfile_fd))
			return (FAILURE);
	}
	return (SUCCESS);
}

// int	exec_single_cmd(t_cmd *cmd_args, t_env *env, bool piped)

int	exec_cmd(t_cmd *cmd_args, t_env *env)
{
	const char	*builtins[] = {CMD_CD, CMD_ECHO, CMD_ENV, CMD_EXPORT, CMD_PWD,
			CMD_UNSET, NULL};
	t_cp		cp;
	pid_t		child_pid;
	int			wait_stat;
	char		**env_arr;

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
			if (child_pid == 0)
			{
				env_arr = get_env_arr(env);
				// close file?
				if (!env_arr)
					exit(EXIT_FAILURE);
				cp.path = get_cmd_path(env, cmd_args->argv[0]);
				if (!cp.path)
				{
					if (errno == EACCES || errno == ENOENT || errno == EISDIR)
						print_cmd_err(cmd_args->argv[0], strerror(errno));
					else
						print_basic_error(cmd_args->argv[0],
							"command not found");
					free_array(&env_arr);
					exit(EXIT_FAILURE);
					// close file
				}
				if (duplicate_files(cmd_args))
					exit(EXIT_FAILURE); // cleanup?
				cp.args = cmd_args->argv;
				// execve
				if (execve(cp.path, cp.args, env_arr))
				{
					free(cp.path);
					free_array(&env_arr);
					perror("execve failed");
					exit(EXIT_FAILURE);
					// close file
				}
			}
			if (waitpid(child_pid, &wait_stat, 0) == -1)
				return (FAILURE);
		}
		// !!!!exit stat code!!!!
		return (SUCCESS);
	}
	while (cmd_args)
	{
		// if (!pipe(pipe_fd))
		// 	return (FAILURE);
		cmd_args = cmd_args->next;
	}
	return (SUCCESS);
}

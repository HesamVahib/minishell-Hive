/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 18:27:27 by michoi            #+#    #+#             */
/*   Updated: 2025/05/17 22:18:28 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execution.h"

pid_t	init_child_process(void)
{
	pid_t	cp;

	cp = fork();
	if (cp == -1)
	{
		perror("Fork failed");
		return (-1);
	}
	return (cp);
}

int	init_pipe(int pipe_fd[2])
{
	if (pipe(pipe_fd))
	{
		perror("pipe failed");
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
		if (close_fd(cmd_arg->infile_fd))
			return (FAILURE);
	}
	if (cmd_arg->outfile_fd > -1)
	{
		if (duplicate_fd(cmd_arg->outfile_fd, STDOUT_FILENO))
			return (FAILURE);
		if (close_fd(cmd_arg->outfile_fd))
			return (FAILURE);
	}
	return (SUCCESS);
}

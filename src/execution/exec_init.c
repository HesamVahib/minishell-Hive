<<<<<<< HEAD:execution/exec_init.c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvahib <hvahib@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 18:27:27 by michoi            #+#    #+#             */
/*   Updated: 2025/06/01 23:48:09 by hvahib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execution.h"

pid_t	init_child_process(void)
{
	pid_t	cp;

	cp = fork();
	if (cp == -1)
		perror("Fork failed");
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

int	duplicate_fd(int old_fd, int new_fd)
{
	int	status;

	status = SUCCESS;
	if (dup2(old_fd, new_fd) == -1)
	{
		perror("dup2 failed");
		status = FAILURE;
	}
	if (close_fd(old_fd))
		status = FAILURE;
	return (status);
}

int	duplicate_files(t_cmd *cmd_arg)
{
	int	status;

	status = SUCCESS;
	if (cmd_arg->infile_fd > -1)
	{
		if (duplicate_fd(cmd_arg->infile_fd, STDIN_FILENO))
			status = FAILURE;
	}
	if (cmd_arg->outfile_fd > -1)
	{
		if (duplicate_fd(cmd_arg->outfile_fd, STDOUT_FILENO))
			status = FAILURE;
	}
	if (cmd_arg->heredoc_fd > -1)
	{
		if (duplicate_fd(cmd_arg->heredoc_fd, STDIN_FILENO))
			status = FAILURE;
	}
	return (status);
}
=======
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 18:27:27 by michoi            #+#    #+#             */
/*   Updated: 2025/06/07 14:49:38 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execution.h"

pid_t	init_child_process(void)
{
	pid_t	cp;

	cp = fork();
	if (cp == -1)
		perror("Fork failed");
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

int	duplicate_fd(int old_fd, int new_fd)
{
	int	status;

	status = SUCCESS;
	if (dup2(old_fd, new_fd) == -1)
	{
		perror("dup2 failed");
		status = FAILURE;
	}
	if (close_fd(old_fd))
		status = FAILURE;
	return (status);
}

int	duplicate_files(t_cmd *cmd_arg)
{
	int	status;

	status = SUCCESS;
	if (cmd_arg->infile_fd > -1)
	{
		if (duplicate_fd(cmd_arg->infile_fd, STDIN_FILENO))
			status = FAILURE;
	}
	if (cmd_arg->outfile_fd > -1)
	{
		if (duplicate_fd(cmd_arg->outfile_fd, STDOUT_FILENO))
			status = FAILURE;
	}
	if (cmd_arg->heredoc_fd > -1)
	{
		if (duplicate_fd(cmd_arg->heredoc_fd, STDIN_FILENO))
			status = FAILURE;
	}
	return (status);
}
>>>>>>> 874a9b48f3199909f568ebc8744a2ebc01ae86ce:src/execution/exec_init.c

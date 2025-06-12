/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_wait.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 19:10:38 by michoi            #+#    #+#             */
/*   Updated: 2025/06/11 16:44:10 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execution.h"

int	wait_for_pid(pid_t pid, int *stat)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	if (waitpid(pid, stat, 0) == -1)
	{
		perror("waitpid failed");
		return (FAILURE);
	}
	return (SUCCESS);
}

/*
	ECHILD: no more children (normal)
	EINTR: Interrupted: try again
*/
static int	wait_for_the_rest(void)
{
	while (1)
	{
		errno = 0;
		if (wait(0) == -1)
		{
			if (errno == ECHILD)
				break ;
			else if (errno == EINTR)
				continue ;
			else
			{
				perror("wait failed");
				return (FAILURE);
			}
		}
	}
	return (SUCCESS);
}

int	handle_exit_status(int wait_stat)
{
	if (WIFEXITED(wait_stat))
		return (WEXITSTATUS(wait_stat));
	if (WIFSIGNALED(wait_stat))
	{
		if (WTERMSIG(wait_stat) == SIGINT)
			ft_putchar_fd('\n', STDERR_FILENO);
		else if (WTERMSIG(wait_stat) == SIGQUIT)
			ft_putendl_fd("Quit (core dumped)", STDERR_FILENO);
		return (128 + WTERMSIG(wait_stat));
	}
	return (-1);
}

int	wait_and_set_exit_status(pid_t last_pid)
{
	int	last_wait_stat;
	int	exit_stat;

	if (wait_for_pid(last_pid, &last_wait_stat))
		return (FAILURE);
	if (wait_for_the_rest())
		return (FAILURE);
	exit_stat = handle_exit_status(last_wait_stat);
	if (exit_stat == -1)
	{
		ft_putendl_fd("Invalid exit status code", STDERR_FILENO);
		return (FAILURE);
	}
	if (set_and_get_exit_status(exit_stat, true) == -1)
	{
		ft_putendl_fd("exit status code assignment failed", STDERR_FILENO);
		return (FAILURE);
	}
	return (SUCCESS);
}

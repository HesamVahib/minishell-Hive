/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 00:44:35 by michoi            #+#    #+#             */
/*   Updated: 2025/06/14 19:46:28 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execution.h"

int	close_fd(int fd)
{
	if (close(fd) == -1)
	{
		perror("close failed");
		return (FAILURE);
	}
	return (SUCCESS);
}

static int	open_heredoc_file(char *limiter)
{
	int		fd;
	char	*filename;

	filename = ft_strjoin(limiter, ".txt");
	if (!filename)
		return (FAILURE);
	fd = open(filename, O_RDONLY);
	free(filename);
	return (fd);
}

static int	open_input_file(t_cmd *cmd)
{
	int	infile_fd;
	int	heredoc_fd;

	if (cmd->redirect_order == 1 && cmd->infile)
	{
		infile_fd = open(cmd->infile, O_RDONLY);
		if (infile_fd == -1)
			return (FAILURE);
		cmd->infile_fd = infile_fd;
	}
	else if (cmd->redirect_order == 2 && cmd->is_heredoc)
	{
		heredoc_fd = open_heredoc_file(cmd->is_heredoc);
		if (heredoc_fd == -1)
			return (FAILURE);
		cmd->heredoc_fd = heredoc_fd;
	}
	return (SUCCESS);
}

int	open_files(t_cmd *cmd_list)
{
	int	outfile_fd;

	if (cmd_list->redirect_order)
	{
		if (open_input_file(cmd_list))
			return (FAILURE);
	}
	if (cmd_list->outfile)
	{
		if (cmd_list->append)
			outfile_fd = open(cmd_list->outfile, O_CREAT | O_WRONLY | O_APPEND,
					0644);
		else
			outfile_fd = open(cmd_list->outfile, O_CREAT | O_WRONLY | O_TRUNC,
					0644);
		if (outfile_fd == -1)
			return (FAILURE);
		cmd_list->outfile_fd = outfile_fd;
	}
	return (SUCCESS);
}

int	close_files(t_cmd *cmd)
{
	if (cmd->infile_fd > -1)
	{
		if (close_fd(cmd->infile_fd))
			return (FAILURE);
	}
	if (cmd->outfile_fd > -1)
	{
		if (close_fd(cmd->infile_fd))
			return (FAILURE);
	}
	if (cmd->heredoc_fd > -1)
	{
		if (close_fd(cmd->heredoc_fd))
			return (FAILURE);
	}
	return (SUCCESS);
}

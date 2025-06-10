<<<<<<< HEAD:execution/exec_open.c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_open.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvahib <hvahib@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 00:44:35 by michoi            #+#    #+#             */
/*   Updated: 2025/06/01 23:46:03 by hvahib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execution.h"

int	close_fd(int fd)
{
	if (close(fd) == -1)
	{
		perror("close failed");
		return (FAILURE);
	}
	return (SUCCESS);
}

int	open_heredoc_file(char *limiter)
{
	int		fd;
	char	*filename;

	filename = ft_strjoin(limiter, ".txt");
	if (!filename)
		return (FAILURE);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (free(filename), -1);
	return (free(filename), fd);
}

int	open_files(t_cmd *cmd_list)
{
	int	infile_fd;
	int	outfile_fd;
	// int	heredoc_fd;

	// printf("%s, %s\n", cmd_list->outfile, cmd_list->infile);
	// Do I have to open heredoc for redirection if I should open the outfile?
	if (cmd_list->is_heredoc && !(cmd_list->outfile))
	{
		puts("am i here?");
		cmd_list->heredoc_fd = open_heredoc_file(cmd_list->is_heredoc);
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
		{
			print_cmd_err(cmd_list->outfile, strerror(errno));
			return (FAILURE);
		}
		cmd_list->outfile_fd = outfile_fd;
	}
	if (cmd_list->infile)
	{
		infile_fd = open(cmd_list->infile, O_RDONLY);
		if (infile_fd == -1)
		{
			print_cmd_err(cmd_list->infile, strerror(errno));
			return (FAILURE);
		}
		cmd_list->infile_fd = infile_fd;
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
	return (SUCCESS);
}
=======
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_open.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 00:44:35 by michoi            #+#    #+#             */
/*   Updated: 2025/06/09 21:24:31 by michoi           ###   ########.fr       */
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

int	open_heredoc_file(char *limiter)
{
	int		fd;
	char	*filename;

	filename = ft_strjoin(limiter, ".txt");
	if (!filename)
		return (FAILURE);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (free(filename), -1);
	return (free(filename), fd);
}

int	open_files(t_cmd *cmd_list)
{
	int	infile_fd;
	int	outfile_fd;
	int	heredoc_fd;

	// printf("%s, %s\n", cmd_list->outfile, cmd_list->infile);
	if (cmd_list->redirect_order && cmd_list->redirect_order == 1)
	{
		if (cmd_list->infile)
		{
			infile_fd = open(cmd_list->infile, O_RDONLY);
			if (infile_fd == -1)
			{
				// print_cmd_err(cmd_list->infile, strerror(errno));
				return (FAILURE);
			}
			cmd_list->infile_fd = infile_fd;
		}
	}
	else if (cmd_list->redirect_order && cmd_list->redirect_order == 2)
	{
		if (cmd_list->is_heredoc)
		{
			heredoc_fd = open_heredoc_file(cmd_list->is_heredoc);
			if (heredoc_fd == -1)
			{
				// print_cmd_err(cmd_list->is_heredoc, strerror(errno));
				return (FAILURE);
			}
			cmd_list->heredoc_fd = heredoc_fd;
		}
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
		{
			print_cmd_err(cmd_list->outfile, strerror(errno));
			return (FAILURE);
		}
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
	return (SUCCESS);
}
>>>>>>> 874a9b48f3199909f568ebc8744a2ebc01ae86ce:src/execution/exec_open.c

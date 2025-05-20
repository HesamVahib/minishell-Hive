/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_open.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 00:44:35 by michoi            #+#    #+#             */
/*   Updated: 2025/05/18 01:06:08 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execution.h"

int	close_fd(int fd)
{
	// printf("closing %d\n", fd);
	if (close(fd))
	{
		perror("close failed");
		return (FAILURE);
	}
	return (SUCCESS);
}

int	open_files(t_cmd *cmd_list)
{
	int	infile_fd;
	// int outfile_fd;

	// printf("%s, %s\n", cmd_list->outfile, cmd_list->infile);

	// if (cmd_list->outfile)
	// {
	// 	if (cmd_list->append)
	// 		outfile_fd = open(cmd_list->outfile, O_CREAT | O_WRONLY | O_APPEND, 0644);
	// 	else
	// 		outfile_fd = open(cmd_list->outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	// 	if (outfile_fd == -1)
	// 	{
	// 		perror("opening or creating outfile failed");
	// 		return (FAILURE);
	// 	}
	// 	cmd_list->outfile_fd = outfile_fd;
	// }

	if (cmd_list->infile)
	{
		infile_fd = open(cmd_list->infile, O_RDONLY);
		if (infile_fd == -1)
		{
			perror("opening or infile failed");
			return (FAILURE);
		}
		cmd_list->infile_fd = infile_fd;
	}
	return (SUCCESS);
}

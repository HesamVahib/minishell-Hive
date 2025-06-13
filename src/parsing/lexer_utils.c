/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 12:40:40 by hvahib            #+#    #+#             */
/*   Updated: 2025/06/11 16:43:03 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool special_char(char *tokenz)
{
	return (ft_strncmp(tokenz, "|", 1) == 0
		|| ft_strncmp(tokenz, "<", 1) == 0 || ft_strncmp(tokenz, ">",
			1) == 0 || ft_strncmp(tokenz, ">>", 2) == 0
		|| ft_strncmp(tokenz, "<<", 2) == 0);
}

int	pipe_counter(char **tokenz)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (tokenz[i])
	{
		if (ft_strncmp(tokenz[i], "|", 1) == 0)
			count++;
		i++;
	}
	return (count);
}

void	init_cmd_list(t_cmd *cmd_list, int n_pipe)
{
	int	k;

	k = 0;
	if (!cmd_list)
		return ;
	while (k <= n_pipe)
	{
		cmd_list[k].error = 0;
		cmd_list[k].infile = NULL;
		cmd_list[k].outfile = NULL;
		cmd_list[k].infile_fd = -1;
		cmd_list[k].outfile_fd = -1;
		cmd_list[k].heredoc_fd = -1;
		cmd_list[k].append = 0;
		cmd_list[k].is_heredoc = NULL;
		cmd_list[k].heredoc_limiters = NULL;
		cmd_list[k].argv = NULL;
		cmd_list[k].is_piped = 0;
		cmd_list[k].redirect_order = 0;
		if (k < n_pipe)
			cmd_list[k].next = &cmd_list[k + 1];
		else
			cmd_list[k].next = NULL;
		if (k > 0)
			cmd_list[k].previous = &cmd_list[k - 1];
		else
			cmd_list[k].previous = NULL;
		k++;
	}
}

int	open_create_files(t_cmd *cmd_list, char *type)
{
	int	fd;
	

	if (ft_strncmp(type, "outfile", 7) == 0)
	{
		if (cmd_list->outfile_fd >= 0)
			close(cmd_list->outfile_fd);
		if (cmd_list->append)
			fd = open(cmd_list->outfile, O_CREAT | O_WRONLY | O_APPEND, 0644);
		else
			fd = open(cmd_list->outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd == -1)
		{
			set_and_get_exit_status(1, true);
			return (-1);
		}
		close(fd);
		return (1);
	}
	else if (ft_strncmp(type, "infile", 6) == 0)
	{
		fd = open(cmd_list->infile, O_RDONLY);
		if (fd == -1)
		{
			// print_cmd_err(cmd_list->infile, strerror(errno));
			set_and_get_exit_status(1, true);
			return (-1);
		}
		close(fd);
		return (1);
	}
	return (0);
}

char	**limiter_collector(char **delim_list, char *new_delim)
{
	char	**new_list;
	int		i;

	i = 0;
	if (delim_list != NULL)
		while (delim_list[i])
			i++;
	new_list = (char **)malloc((i + 2) * sizeof(char *));
	if (!new_list)
		return (NULL);
	if (delim_list != NULL)
	{
		ft_memcpy(new_list, delim_list, i * (sizeof(char *)));
		free(delim_list);
	}
	new_list[i] = ft_strdup(new_delim);
	if (!new_list[i])
		return (free(new_list), free(delim_list), NULL);
	new_list[i + 1] = NULL;
	return (new_list);
}

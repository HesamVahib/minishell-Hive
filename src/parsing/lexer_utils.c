/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 12:40:40 by hvahib            #+#    #+#             */
/*   Updated: 2025/06/14 20:16:24 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	special_char(char *tokenz)
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
			return (set_and_get_exit_status(errno, true), -1);
		return (close(fd), 1);
	}
	else if (ft_strncmp(type, "infile", 6) == 0)
	{
		fd = open(cmd_list->infile, O_RDONLY);
		if (fd == -1)
			return (set_and_get_exit_status(errno, true), -1);
		return (close(fd), 1);
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

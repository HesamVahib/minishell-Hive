/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 16:50:33 by michoi            #+#    #+#             */
/*   Updated: 2025/01/05 01:52:46 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*initialize_line(char buffer[])
{
	size_t	buffer_len;
	char	*line;

	buffer_len = ft_strlen(buffer);
	line = malloc(buffer_len + 1);
	if (!line)
		return (0);
	line[0] = '\0';
	if (buffer_len)
		ft_strcpy(line, buffer);
	return (line);
}

static char	*read_line(int fd, char buffer[])
{
	char	*line;
	ssize_t	read_bytes;

	line = initialize_line(buffer);
	if (!line)
		return (0);
	if (get_idx(line, '\n') != -1)
		return (line);
	while (1)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes <= 0)
		{
			if (read_bytes < 0 || !*line)
				return (free(line), (char *)0);
			break ;
		}
		buffer[read_bytes] = '\0';
		line = ft_strjoin(line, buffer);
		if (!line || get_idx(line, '\n') != -1)
			break ;
	}
	return (line);
}

static char	*extract_line(char **line, char leftover[])
{
	int		i;
	char	*complete_line;

	if ((!*line) || (!**line))
		return (0);
	i = get_idx(*line, '\n');
	if (i == -1)
	{
		complete_line = ft_substr(*line, 0, ft_strlen(*line));
		if (!complete_line)
			return (free(*line), leftover[0] = '\0', (char *)0);
		leftover[0] = '\0';
	}
	else
	{
		complete_line = ft_substr(*line, 0, (i + 1));
		if (!complete_line)
			return (free(*line), leftover[0] = '\0', (char *)0);
		ft_strcpy(leftover, (*line + i + 1));
	}
	free(*line);
	*line = 0;
	return (complete_line);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*read_content;
	char		*complete_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	read_content = read_line(fd, buffer);
	if (!read_content)
		return (0);
	complete_line = extract_line(&read_content, buffer);
	return (complete_line);
}

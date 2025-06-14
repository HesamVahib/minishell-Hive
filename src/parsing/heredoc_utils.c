/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 12:40:30 by hvahib            #+#    #+#             */
/*   Updated: 2025/06/11 16:42:57 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	sigint_handler_heredoc(int sig)
{
	(void)sig;
	g_signal = SIGINT;
}

void	write_heredoc_content(int fd, char *limiter)
{
	char	*line;
	char	*temp;

	signal(SIGINT, sigint_handler_heredoc);
	rl_event_hook = sig_handler_heredoc;
	while (1)
	{
		line = readline("> ");
		if (!line || g_signal == SIGINT)
			break ;
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
		{
			free(line);
			break ;
		}
		temp = ft_strjoin(line, "\n");
		if (temp)
			write(fd, temp, ft_strlen(temp));
		free(line);
		free(temp);
	}
}

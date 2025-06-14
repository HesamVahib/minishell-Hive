/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 12:40:30 by hvahib            #+#    #+#             */
/*   Updated: 2025/06/11 16:42:57 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*find_last_limiter(char **limiters)
{
	int		i;
	char	*main_limiter;

	i = 0;
	main_limiter = NULL;
	while (limiters[i])
	{
		if (!limiters[i + 1])
		{
			main_limiter = ft_strdup(limiters[i]);
			return (main_limiter);
		}
		i++;
	}
	return (NULL);
}

static void	heredoc_setup(char **limiters, char **main_limiter)
{
	*main_limiter = find_last_limiter(limiters);
	rl_on_new_line();
	rl_replace_line("", 0);
}

static int	heredoc_loop(char **limiters, char *main_limiter)
{
	int	fd;
	int	i;

	i = 0;
	while (limiters[i] != NULL)
	{
		fd = open_heredoc_file(main_limiter);
		if (fd == -1 || g_signal == SIGINT)
			return (1);
		write_heredoc_content(fd, limiters[i]);
		close(fd);
		i++;
	}
	return (0);
}

void	open_heredoc(char **limiters)
{
	char	*main_limiter;
	int		stop;

	heredoc_setup(limiters, &main_limiter);
	stop = heredoc_loop(limiters, main_limiter);
	free(main_limiter);
	if (stop)
		return ;
}

int	heredoc_processing(t_cmd *cmd_args)
{
	if (!cmd_args)
		return (0);
	while (cmd_args && cmd_args->is_heredoc)
	{
		open_heredoc(cmd_args->heredoc_limiters);
		if (g_signal == SIGINT)
		{
			rl_event_hook = NULL;
			return (0);
		}
		cmd_args = cmd_args->next;
	}
	rl_event_hook = NULL;
	return (1);
}

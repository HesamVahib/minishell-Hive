/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvahib <hvahib@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 12:40:30 by hvahib            #+#    #+#             */
/*   Updated: 2025/06/01 23:34:24 by hvahib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

static void	sigint_handler_heredoc(int sig)
{
	(void)sig;
	g_signal = SIGINT;
}

static int	open_heredoc_file(char *limiter)
{
	int	fd;
	char *filename;

	filename = ft_strjoin(limiter, ".txt");
	if (!filename)
		return (-1);
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (free(filename), -1);
	return (free(filename), fd);
}

static void	write_heredoc_content(int fd, char *limiter)
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

static	char *find_last_limiter(char **limiters)
{
	int	i;
	char *main_limiter;
	
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

static	void	open_heredoc(char **limiters)
{
	int		fd;
	char	*main_limiter;
	int		i;
	char	*filename;

	i = 0;
	main_limiter = find_last_limiter(limiters);
	filename = NULL;
	rl_on_new_line();
	rl_replace_line("", 0);
	while (limiters[i] != NULL)
	{
		fd = open_heredoc_file(main_limiter);
		if (fd == -1 || g_signal == SIGINT)
			return (free(main_limiter));
		write_heredoc_content(fd, limiters[i]);
		close(fd);
		i++;
	}
	free(main_limiter);
}

int	heredoc_processing(t_cmd *cmd_args)
{
	t_cmd	*temp;

	if (!cmd_args)
		return (0);
	temp = cmd_args;

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

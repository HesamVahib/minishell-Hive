/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvahib <hvahib@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 12:40:30 by hvahib            #+#    #+#             */
/*   Updated: 2025/05/11 18:01:01 by hvahib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

static void	sigint_handler_heredoc(int sig)
{
	(void)sig;
	g_signal = SIGINT;
}

static int	open_heredoc_file(char *limiter, char **filename)
{
	int	fd;

	*filename = ft_strjoin(limiter, ".txt");
	if (!(*filename))
		return (-1);
	fd = open(*filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (-1);
	return (fd);
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
	if (line)
		free(line);
}

char	*open_heredoc(char **limiters)
{
	int		fd;
	char	*filename;
	int		i;

	i = 0;
	filename = NULL;
	rl_on_new_line();
	rl_replace_line("", 0);
	while (limiters[i] != NULL)
	{
		printf("in open\n");
		if (filename)
		{
			remove(filename);
			free(filename);
		}
		fd = open_heredoc_file(limiters[i], &filename);
		if (fd == -1)
			return (free(filename), NULL);
		write_heredoc_content(fd, limiters[i]);
		close(fd);
		i++;
	}
	return (filename);
}

int	is_all_heredoc(t_cmd *cmd)
{
	while (cmd)
	{
		if (cmd->is_heredoc == NULL)
			return (0);
		cmd = cmd->next;
	}
	return (1);
}

int	heredoc_processing(t_cmd *cmd_args)
{
	t_cmd	*temp;
	char	*txt_filename;

	temp = cmd_args;
	txt_filename = NULL;
	if (!is_all_heredoc(temp))
		return (0);
	while (cmd_args && cmd_args->is_heredoc)
	{
		if (txt_filename)
			remove(txt_filename);
		txt_filename = open_heredoc(cmd_args->heredoc_limiters);
		if (g_signal == SIGINT)
		{
			if (txt_filename)
				remove(txt_filename);
			rl_event_hook = NULL;
			return (free(txt_filename), 0);
		}
		cmd_args = cmd_args->next;
	}
	rl_event_hook = NULL;
	return (1);
}

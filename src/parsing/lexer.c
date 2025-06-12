/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 12:41:02 by hvahib            #+#    #+#             */
/*   Updated: 2025/06/11 18:37:18 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	handle_file_redirection(t_cmd *cur, char **tokenz, int *i,
		char mode)
{
	if (!cur->error)
	{
		if (mode == 'i')
		{
			if (tokenz[*i + 1])
				cur->infile = ft_strdup(tokenz[*i + 1]);
			else
				cur->infile = ft_strdup(tokenz[*i]);
			if (open_create_files(cur, "infile") == -1)
				cur->error = 2;
		}
		else if (mode == 'o' || mode == 'a')
		{
			if (tokenz[*i + 1])
				cur->outfile = ft_strdup(tokenz[*i + 1]);
			else
				cur->outfile = ft_strdup(tokenz[*i]);
			cur->append = (mode == 'a');
			if (open_create_files(cur, "outfile") == -1)
			{
				// printf("error opening outfile\n");
				cur->error = 1;
			}
		}
	}
	*i = *i + 2;
	cur->redirect_order = 1;
}

static void	handle_heredoc(t_cmd *cur, char **tokenz, int *i)
{
	if (!tokenz[*i + 1])
	{
		printf("syntax error near unexpected token `%c'\n", tokenz[*i][0]);
		set_and_get_exit_status(2, true);
		cur->error = 1;
		return ;
	}
	cur->is_heredoc = ft_strdup(tokenz[*i + 1]);
	cur->heredoc_limiters = limiter_collector(cur->heredoc_limiters,
			cur->is_heredoc);
	*i = *i + 2;
	cur->redirect_order = 2;
}

static void	extract_arguments(t_cmd *cur, char **tokenz, int *i)
{
	int	argc;
	int	k;
	int	j;
	int start;

	k = 0;
	j = *i;
	start = (*i);
	argc = count_arguments(tokenz, &j);
	cur->argv = ft_calloc(argc + 1, sizeof(char *));
	if (!cur->argv)
		return ;
	while (*i < j)
	{
		if (is_redirection(tokenz[*i]))
		{
			(*i)++;
			if (tokenz[*i])
				(*i)++;
		}
		else
			cur->argv[k++] = ft_strdup(tokenz[(*i)++]);
	}
	(*i) = start;
	cur->argv[k] = NULL;
}

static void	parse_tokens(t_cmd *cmd_list, char **tokenz)
{
	int		i;
	t_cmd	*cur;

	i = 0;
	cur = cmd_list;
	while (tokenz && tokenz[i])
	{
		extract_arguments(cur, tokenz, &i);
		while (tokenz[i] && !is_pipe(tokenz[i]))
		{
			if (ft_strncmp(tokenz[i], "<", 1) == 0 && tokenz[i][1] != '<')
				handle_file_redirection(cur, tokenz, &i, 'i');
			else if (ft_strncmp(tokenz[i], ">", 1) == 0 && tokenz[i][1] != '>')
				handle_file_redirection(cur, tokenz, &i, 'o');
			else if (ft_strncmp(tokenz[i], ">>", 2) == 0)
				handle_file_redirection(cur, tokenz, &i, 'a');
			else if (ft_strncmp(tokenz[i], "<<", 2) == 0)
				handle_heredoc(cur, tokenz, &i);
			else
				i++;
			if (i >= arrlen(tokenz))
				return ;
		}
		if (tokenz[i] && is_pipe(tokenz[i]))
			handle_next_command(&cur, &i);
	}
}

t_cmd	*cmd_args_extractor(char **tokenz)
{
	t_cmd	*cmd_list;
	int		n_pipe;

	n_pipe = pipe_counter(tokenz);
	cmd_list = ft_calloc(n_pipe + 1, sizeof(t_cmd));
	if (!cmd_list)
		return (NULL);
	init_cmd_list(cmd_list, n_pipe);
	parse_tokens(cmd_list, tokenz);
	return (cmd_list);
}

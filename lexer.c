/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 12:41:02 by hvahib            #+#    #+#             */
/*   Updated: 2025/05/15 22:56:28 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

static void	handle_file_redirection(t_cmd *cur, char **tokenz, int *i,
		char mode)
{
	if (mode == 'i')
	{
		cur->infile = ft_strdup(tokenz[*i + 1]);
		if (!open_create_files(cur, "infile"))
			printf("error opening infile\n");
	}
	else if (mode == 'o' || mode == 'a')
	{
		cur->outfile = ft_strdup(tokenz[*i + 1]);
		cur->append = (mode == 'a');
		if (!open_create_files(cur, "outfile"))
			printf("error opening outfile\n");
	}
	*i = *i + 2;
}

static void	handle_heredoc(t_cmd *cur, char **tokenz, int *i)
{
	if (!tokenz[*i + 1])
	{
		printf("syntax error near unexpected token `newline'\n");
		return ;
	}
	cur->is_heredoc = ft_strdup(tokenz[*i + 1]);
	cur->heredoc_limiters = limiter_collector(cur->heredoc_limiters,
			cur->is_heredoc);
	// *i = *i + 2;
	*i = *i + 1;
}

static void	extract_arguments(t_cmd *cur, char **tokenz, int *i)
{
	int	argc;
	int	arg_start;
	int	k;

	arg_start = *i;
	argc = 0;
	while (tokenz[*i] && ft_strncmp(tokenz[*i], "|", 1) != 0
		&& ft_strncmp(tokenz[*i], "<", 1) != 0 && ft_strncmp(tokenz[*i], ">",
			1) != 0 && ft_strncmp(tokenz[*i], ">>", 2) != 0
		&& ft_strncmp(tokenz[*i], "<<", 2) != 0)
	{
		*i = *i + 1;
		argc++;
	}
	cur->argv = ft_calloc(argc + 1, sizeof(char *));
	k = 0;
	while (k < argc)
	{
		cur->argv[k] = ft_strdup(tokenz[arg_start + k]);
		k++;
	}
	cur->argv[argc] = NULL;
}

static void	parse_tokens(t_cmd *cmd_list, char **tokenz)
{
	int		i;
	t_cmd	*cur;

	i = 0;
	cur = &cmd_list[0];
	while (tokenz && tokenz[i] != NULL)
	{
		if (!tokenz)
			return ;
		if (tokenz[i] && ft_strncmp(tokenz[i], "<", 1) == 0
			&& tokenz[i][1] != '<')
			handle_file_redirection(cur, tokenz, &i, 'i');
		else if (tokenz[i] && ft_strncmp(tokenz[i], ">", 1) == 0
			&& tokenz[i][1] != '>')
			handle_file_redirection(cur, tokenz, &i, 'o');
		else if (tokenz[i] && ft_strncmp(tokenz[i], ">>", 2) == 0)
			handle_file_redirection(cur, tokenz, &i, 'a');
		else if (tokenz[i] && ft_strncmp(tokenz[i], "<<", 2) == 0)
			handle_heredoc(cur, tokenz, &i);
		else if (tokenz[i] && ft_strncmp(tokenz[i], "|", 1) == 0)
		{
			cur->is_piped = 1;
			if (cur->next)
				cur = cur->next;
			i++;
		}
		else if (tokenz[i])
			extract_arguments(cur, tokenz, &i);
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

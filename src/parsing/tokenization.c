/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 12:42:40 by hvahib            #+#    #+#             */
/*   Updated: 2025/06/11 18:23:49 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	**tokenize_and_check(char *new_line)
{
	char	**cmd_line;

	if (!new_line)
		return (NULL);
	cmd_line = word_splitter(new_line);
	if (!cmd_line || !*cmd_line)
	{
		free_array(&cmd_line);
		return (printf("it is not splitted properly\n"), NULL);
	}
	cmd_line = quotes_chkr(cmd_line);
	if (!cmd_line || !*cmd_line)
	{
		free_array(&cmd_line);
		return (printf("the quotes are not closed\n"), NULL);
	}
	cmd_line = syntax_analyzer(cmd_line);
	if (!cmd_line || !*cmd_line)
	{
		free_array(&cmd_line);
		return (printf("syntax_analyzer error\n"), NULL);
	}
	return (cmd_line);
}

static char	**expand_variables(char **cmd_line, t_env *env)
{
	cmd_line = dollar_expansion(cmd_line, env);
	if (!cmd_line)
		return (printf("Dollar Expansion failed\n"), NULL);
	return (cmd_line);
}

char	**line_tokenized(char *line, t_env *env)
{
	char	**cmd_line;
	char	**expanded_line;

	cmd_line = tokenize_and_check(line);
	if (!cmd_line)
		return (NULL);
	
	expanded_line = expand_variables(cmd_line, env);
	if (!expanded_line)
	{
		free_array(&cmd_line);  // Free the original array
		return (printf("Dollar Expansion failed\n"), NULL);
	}
	free_array(&cmd_line);
	cmd_line = adjacent_quotes(expanded_line);
	if (!cmd_line || !*cmd_line)
	{
		free_array(&cmd_line);
		return (printf("adjacent quotes handling failed\n"), NULL);
	}
	return (cmd_line);
}

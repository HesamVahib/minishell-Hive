/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvahib <hvahib@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 12:42:40 by hvahib            #+#    #+#             */
/*   Updated: 2025/06/11 21:04:19 by hvahib           ###   ########.fr       */
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
		return (free_array(&cmd_line),
			printf("it is not splitted properly\n"),
			NULL);
	if (!quotes_chkr(cmd_line))
		return (free_array(&cmd_line),
			printf("the quotes are not closed\n"),
			NULL);
	if (!syntax_analyzer(cmd_line))
		return (free_array(&cmd_line),
			printf("syntax_analyzer error\n"),
			NULL);
	return (cmd_line);
}

static char	**expand_variables(char **cmd_line, t_env *env)
{
	char	**new_cmd;

	new_cmd = dollar_expansion(cmd_line, env);
	if (!new_cmd)
		return (printf("Dollar Expansion failed\n"), NULL);
	return (new_cmd);
}

char	**line_tokenized(char *line, t_env *env)
{
	char	**cmd_line;
	char	**expanded_line;
	char	**final_line;

	cmd_line = tokenize_and_check(line);
	if (!cmd_line)
		return (NULL);
	expanded_line = expand_variables(cmd_line, env);
	if (!expanded_line)
	{
		free_array(&cmd_line);
		return (printf("Dollar Expansion failed\n"), NULL);
	}
	final_line = adjacent_quotes(expanded_line);
	if (!final_line || !*final_line)
	{
		free_array(&expanded_line);
		return (printf("adjacent quotes handling failed\n"), NULL);
	}
	free_array(&cmd_line);
	free_array(&expanded_line);
	return (final_line);
}

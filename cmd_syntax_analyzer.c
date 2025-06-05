/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_syntax_analyzer.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 12:39:15 by hvahib            #+#    #+#             */
/*   Updated: 2025/06/03 18:35:46 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

// Checks if a token is a special operator
static int	is_operator(char *token)
{
	return (!ft_strncmp(token, "<<", 2) || !ft_strncmp(token, ">>", 2)
		|| !ft_strncmp(token, "<", 1) || !ft_strncmp(token, ">", 1)
		|| !ft_strncmp(token, "|", 1) || !ft_strncmp(token, ";", 1));
}

// Checks for syntax errors between consecutive tokens
static int	check_consecutive_ops(char **tokenz, int i)
{
	if (!tokenz[i + 1] || (is_operator(tokenz[i + 1]) && tokenz[i][0] != '|'))
	{
		if (!tokenz[i + 1])
			return (printf("syntax error near unexpected token `newline'\n"),
					1);
		return (printf("syntax error near unexpected token `%s'\n",
				tokenz[i + 1]), 1);
	}
	return (0);
}

char	**syntax_analyzer(char **tokenz)
{
	int	i;

	i = 0;
	while (tokenz[i])
	{
		if (!ft_strncmp(tokenz[i], "|", 1) && i == 0)
			return (printf("syntax error near unexpected token `%s'\n",
					tokenz[i]), NULL); //leak
		if (is_operator(tokenz[i]))
		{
			if (check_consecutive_ops(tokenz, i))
				return (NULL); //leak
		}
		i++;
	}
	return (tokenz);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_syntax_analyzer.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 12:39:15 by hvahib            #+#    #+#             */
/*   Updated: 2025/06/11 16:41:13 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	is_operator(char *token)
{
	return (!ft_strncmp(token, "<<", 2) || !ft_strncmp(token, ">>", 2)
		|| !ft_strncmp(token, "<", 1) || !ft_strncmp(token, ">", 1)
		|| !ft_strncmp(token, "|", 1) || !ft_strncmp(token, ";", 1));
}

static int	check_consecutive_ops(char **tokenz, int i)
{
	if (!tokenz[i + 1] || (is_operator(tokenz[i + 1]) && tokenz[i][0] != '|'))
	{
		set_and_get_exit_status(2, true);
		printf("(what the)shell: syntax error near unexpected \
				token `%c'\n", tokenz[i][0]);
		return (1);
	}
	return (0);
}

char	**syntax_analyzer(char **tokenz)
{
	int	i;

	i = 0;
	while (tokenz[i])
	{
		if ((!ft_strncmp(tokenz[i], "|", 1)
				|| !ft_strncmp(tokenz[i], ";", 1)) && i == 0)
			return (printf("(what the)shell: syntax error near \
										unexpected token `%s'\n",
					tokenz[i]), NULL);
		if (is_operator(tokenz[i]))
		{
			if (check_consecutive_ops(tokenz, i))
				return (NULL);
		}
		i++;
	}
	return (tokenz);
}

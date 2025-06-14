/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenz_util_wsplitter2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 12:42:52 by hvahib            #+#    #+#             */
/*   Updated: 2025/06/10 13:36:15 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	skip_quoted_section(char *line, int i)
{
	char	quote;

	quote = line[i];
	i++;
	while (line[i] && line[i] != quote)
		i++;
	if (line[i] == quote)
		i++;
	return (i);
}

int	handle_regular_word(char **splitted_line, char *line, int i, int *j)
{
	int		start;
	char	*new_token;

	start = i;
	while (line[i] && line[i] != ' ' && line[i] != '<' && line[i] != '>'
		&& line[i] != '|')
	{
		if (line[i] == '\'' || line[i] == '"')
			i = skip_quoted_section(line, i);
		else
			i++;
	}
	new_token = ft_strndup(&line[start], i - start);
	if (!new_token)
		return (-1);
	splitted_line[*j] = new_token;
	*j = *j + 1;
	return (i);
}

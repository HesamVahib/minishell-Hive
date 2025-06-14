/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenz_util_wsplitter.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 12:42:52 by hvahib            #+#    #+#             */
/*   Updated: 2025/06/10 13:36:15 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	skip_spaces(char *line, int i)
{
	while (line[i] == ' ')
		i++;
	return (i);
}

static int	handle_double_operator(char **splitted_line, char *line, int i,
		int *j)
{
	splitted_line[*j] = ft_strndup(&line[i], 2);
	if (!splitted_line[*j])
		return (-1);
	if (splitted_line[*j])
		*j = *j + 1;
	return (i + 2);
}

static int	handle_single_operator(char **splitted_line, char *line, int i,
		int *j)
{
	splitted_line[*j] = ft_strndup(&line[i], 1);
	if (!splitted_line[*j])
		return (-1);
	if (splitted_line[*j])
		*j = *j + 1;
	return (i + 1);
}

static int	process_next_token(char **splitted_line, char *line, int i, int *j)
{
	if ((line[i] == '<' || line[i] == '>') && line[i + 1] == line[i])
		return (handle_double_operator(splitted_line, line, i, j));
	else if (line[i] == '<' || line[i] == '>' || line[i] == '|')
		return (handle_single_operator(splitted_line, line, i, j));
	else
		return (handle_regular_word(splitted_line, line, i, j));
}

char	**word_splitter(char *line)
{
	int		size;
	char	**splitted_line;
	int		i;
	int		j;

	if (!line)
		return (NULL);
	size = ft_cmdlen(line);
	splitted_line = (char **)ft_calloc(size + 1, sizeof(char *));
	if (!splitted_line)
		return (NULL);
	i = 0;
	j = 0;
	while (line[i])
	{
		i = skip_spaces(line, i);
		if (!line[i])
			break ;
		i = process_next_token(splitted_line, line, i, &j);
		if (i == -1)
			return (free_array(&splitted_line), NULL);
	}
	splitted_line[j] = NULL;
	return (splitted_line);
}

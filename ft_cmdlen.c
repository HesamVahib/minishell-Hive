/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmdlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvahib <hvahib@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 12:40:25 by hvahib            #+#    #+#             */
/*   Updated: 2025/05/08 12:40:28 by hvahib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

static int	skip_spaces(char *line, int i)
{
	while (line[i] == ' ')
		i++;
	return (i);
}

static int	handle_token(char *line, int *i)
{
	char	quote;

	if (line[*i] == '\'' || line[*i] == '"')
	{
		quote = line[*i];
		(*i)++;
		while (line[*i] && line[*i] != quote)
			(*i)++;
		if (line[*i] == quote)
			(*i)++;
	}
	else if ((line[*i] == '<' || line[*i] == '>') && line[*i + 1] == line[*i])
		(*i) += 2;
	else if (line[*i] == '<' || line[*i] == '>' || line[*i] == '|')
		(*i)++;
	else
	{
		while (line[*i] && line[*i] != ' ' && line[*i] != '<' && line[*i] != '>'
			&& line[*i] != '|')
			(*i)++;
	}
	return (1);
}

int	ft_cmdlen(char *line)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	i = skip_spaces(line, i);
	while (line[i])
	{
		j += handle_token(line, &i);
		i = skip_spaces(line, i);
	}
	return (j);
}

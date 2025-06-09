/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenz_util_quotes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvahib <hvahib@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 12:42:47 by hvahib            #+#    #+#             */
/*   Updated: 2025/06/09 17:49:59 by hvahib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**quotes_chkr(char **cmd_line)
{

	int	in_single;
	int	in_double;
	int	i;
	int	j;

	in_single = 0;
	in_double = 0;
	i = 0;
	while (cmd_line[i])
	{
		j = 0;
		while (cmd_line[i][j])
		{
			if (cmd_line[i][j] == '\'' && !in_double)
				in_single = !in_single;
			else if (cmd_line[i][j] == '\"' && !in_single)
				in_double = !in_double;
			j++;
		}
		i++;
	}
	if (in_single || in_double)
		return (NULL);
	return (cmd_line);

}

char	*remove_adjacent_quotes(char *str)
{
	char	*new_str;
	int		j;
	int		k;
	char	current_quote;
	int		in_quote;

	new_str = malloc(strlen(str) + 1);
	if (!new_str)
		return (NULL);
	j = 0;
	k = 0;
	in_quote = 0;
	current_quote = 0;
	while (str[j])
	{
		if ((str[j] == '\'' || str[j] == '"') && !in_quote)
		{
			current_quote = str[j];
			in_quote = 1;
			j++;
		}
		else if (in_quote && str[j] == current_quote)
		{
			in_quote = 0;
			j++;
		}
		else
			new_str[k++] = str[j++];
	}
	new_str[k] = '\0';
	return (new_str);

}

char	**adjacent_quotes(char **cmd_line)
{
	int		i;
	char	*new_str;

	i = 0;
	while (cmd_line[i])
	{
		new_str = remove_adjacent_quotes(cmd_line[i]);
		if (new_str)
			free(cmd_line[i]);
		else
			return (NULL);
		cmd_line[i] = new_str;
		i++;
	}
	return (cmd_line);
}

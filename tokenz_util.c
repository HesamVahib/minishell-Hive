/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenz_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvahib <hvahib@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 12:42:57 by hvahib            #+#    #+#             */
/*   Updated: 2025/05/26 16:20:08 by hvahib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

char	*double_backslash_remover(char *cmd_line)
{
	int		i;
	char	*new_str;
	char	*temp;

	i = 0;
	new_str = ft_strdup("");
	while (cmd_line[i])
	{
		if (cmd_line[i] == '\\'
			&& (cmd_line[i + 1])
			&& ((cmd_line[i + 1]) == '\\' || cmd_line[i + 1] == '$'))
			i++;
		temp = append_char(new_str, cmd_line[i]);
		if (!temp)
		{
			free(new_str);
			return (NULL);
		}
		new_str = temp;
		i++;
	}
	return (new_str);
}

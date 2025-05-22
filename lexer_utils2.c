/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvahib <hvahib@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:34:02 by hvahib            #+#    #+#             */
/*   Updated: 2025/05/22 16:34:15 by hvahib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int	count_arguments(char **tokenz)
{
	int argc = 0;
	int i = 0;

	while (tokenz[i])
	{
		if (special_char(tokenz[i]))
		{
			if (ft_strncmp(tokenz[i], "|", 1) == 0)
				i += 1;
			else
				i += 2;
		}
		else
		{
			argc++;
			i++;
		}
	}
	return (argc);
}
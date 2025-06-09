/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:34:02 by hvahib            #+#    #+#             */
/*   Updated: 2025/06/07 14:51:09 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int count_arguments(char **tokenz, int *j)
{
    int argc = 0;
    
    while (tokenz[*j] && !is_pipe(tokenz[*j]))
    {
        if (is_redirection(tokenz[*j]))
        {
            (*j)++;
            if (tokenz[*j])
                (*j)++;
        }
        else
        {
            argc++;
            (*j)++;
        }
    }
    return argc;
}

int	is_redirection(const char *token)
{
	return (ft_strncmp(token, "<", 1) == 0 || ft_strncmp(token, ">", 1) == 0
		|| ft_strncmp(token, ">>", 2) == 0 || ft_strncmp(token, "<<", 2) == 0);
}

int	is_pipe(const char *token)
{
	return (ft_strncmp(token, "|", 1) == 0);
}

void	handle_next_command(t_cmd **cur, int *i)
{
	(*cur)->is_piped = 1;
	if ((*cur)->next)
		*cur = (*cur)->next;
	(*i)++;
}
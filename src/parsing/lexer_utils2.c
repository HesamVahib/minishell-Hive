/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:34:02 by hvahib            #+#    #+#             */
/*   Updated: 2025/06/11 16:43:05 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	count_arguments(char **tokenz, int *j)
{
	int	argc;

	argc = 0;
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
	return (argc);
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

void	extract_arguments(t_cmd *cur, char **tokenz, int *i)
{
	int		argc;
	int		k;
	int		j;
	int		start;

	k = 0;
	j = *i;
	start = (*i);
	argc = count_arguments(tokenz, &j);
	cur->argv = ft_calloc(argc + 1, sizeof(char *));
	if (!cur->argv)
		return ;
	while (*i < j)
	{
		if (is_redirection(tokenz[*i]))
		{
			(*i)++;
			if (tokenz[*i])
				(*i)++;
		}
		else
			cur->argv[k++] = ft_strdup(tokenz[(*i)++]);
	}
	(*i) = start;
	cur->argv[k] = NULL;
}

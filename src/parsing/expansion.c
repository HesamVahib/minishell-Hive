/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 12:39:57 by hvahib            #+#    #+#             */
/*   Updated: 2025/06/11 16:41:29 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	dollar_validated(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if ((str[i] == '$' && str[i + 1] && str[i + 1] == '\'') && (str[i - 1]
				&& str[i - 1] != '$'))
			return (0);
		i++;
	}
	return (1);
}

char	*stitch_strings(char **temp_split)
{
	int		i;
	char	*result;
	char	*temp;

	if (!temp_split || !*temp_split)
		return (NULL);
	result = ft_strdup("");
	if (!result)
		return (NULL);
	i = 0;
	while (temp_split[i])
	{
		temp = ft_strjoin(result, temp_split[i]);
		free(result);
		if (!temp)
			return (NULL);
		result = temp;
		i++;
	}
	return (result);
}

static char	*expand_single_token(char *token, t_env *env)
{
	char	*new_token;

	new_token = process_dollars(token, env);
	if (!new_token)
		return (free(new_token), NULL);
	return (new_token);
}

static char	*copy_or_expand_token(char **tokenz, int i, t_env *env)
{
	char	*new_token;
	char	*temp;

	if ((tokenz[i][0] == '$'
		&& tokenz[i][1] && tokenz[i][1] == '?'))
	{
		temp = ft_itoa(set_and_get_exit_status(0, false));
		new_token = ft_strjoin(temp, &tokenz[i][2]);
		free(temp);
	}
	else
	{
		if (dollar_validated(tokenz[i]) == 1)
		{
			new_token = expand_single_token(tokenz[i], env);
			if (!new_token)
				return (NULL);
		}
		else
			new_token = ft_strdup(tokenz[i]);
	}
	return (new_token);
}

char	**dollar_expansion(char **tokenz, t_env *env)
{
	char	**res;
	int		i;

	res = malloc((arrlen(tokenz) + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	i = -1;
	while (tokenz[++i])
	{
		if ((tokenz[i][0] == '\\') || (tokenz[i][0] == '\''
			&& tokenz[i][ft_strlen(tokenz[i]) - 1] == '\'')
			|| (tokenz[i][0] == '$' && !tokenz[i][1]))
		{
			res[i] = ft_strdup(tokenz[i]);
			if (!res[i])
				return (free_array(&res), NULL);
			continue ;
		}
		res[i] = copy_or_expand_token(tokenz, i, env);
		if (!res[i])
			return (free_array(&res), NULL);
	}
	res[i] = NULL;
	return (res);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvahib <hvahib@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 12:43:09 by hvahib            #+#    #+#             */
/*   Updated: 2025/06/09 20:30:20 by hvahib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char *ft_strndup(const char *s, int n)
{
    char *dup;
    int i;

    if (!s || n < 0)
        return (NULL);
    dup = ft_calloc(n + 1, sizeof(char));
    if (!dup)
        return (NULL);

    i = 0;
    while (i < n && s[i])
	{
        dup[i] = s[i];
        i++;
    }
    return (dup);
}

bool	is_in_array(const char **arr, char *s)
{
	if (!arr || !*arr || !s || !*s)
		return (false);
	while (*arr)
	{
		if (!ft_strncmp(*arr, s, ft_strlen(s)))
			return (true);
		arr++;
	}
	return (false);
}

int	envlen(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvahib <hvahib@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 12:43:09 by hvahib            #+#    #+#             */
/*   Updated: 2025/05/29 22:27:34 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

char	*ft_strndup(const char *s, int n)
{
	char	*dup;
	int		i;

    i = 0;
    dup = malloc(n + 1);
    if (!dup)
        return NULL;
    while (i < n)
    {
        dup[i] = s[i];
        i++;
    }
    dup[n] = '\0';
    return dup;
}

bool	is_in_array(const char **arr, char *s)
{
	if (!arr || !*arr || !s || !*s)
		return (false);
	while (arr[i])
	{
		if (!ft_strncmp(*arr, s, ft_strlen(s)))
			return (true);
		i++;
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 20:20:28 by michoi            #+#    #+#             */
/*   Updated: 2025/06/11 22:58:55 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execution.h"

static void	cleanup_env_arr(char **env_arr, int i)
{
	env_arr[i] = NULL;
	free_array(&env_arr);
}

static char	*get_key_value(t_env *env)
{
	char	*temp;
	char	*env_value;

	temp = ft_strjoin(env->key, "=");
	if (!temp)
		return (NULL);
	env_value = ft_strjoin(temp, env->value);
	free(temp);
	if (!env_value)
		return (NULL);
	return (env_value);
}

char	**get_env_arr(t_env *env)
{
	char	**env_arr;
	char	*env_value;
	int		i;

	if (!env)
		return (NULL);
	env_arr = malloc(sizeof(*env_arr) * (envlen(env) + 1));
	if (!env_arr)
		return (NULL);
	i = 0;
	while (env)
	{
		if (env->value && *(env->value))
		{
			env_value = get_key_value(env);
			if (!env_value)
				return (cleanup_env_arr(env_arr, i), NULL);
			env_arr[i] = env_value;
			i++;
		}
		env = env->next;
	}
	env_arr[i] = NULL;
	return (env_arr);
}

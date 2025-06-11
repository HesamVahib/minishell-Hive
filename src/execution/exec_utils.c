/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 20:20:28 by michoi            #+#    #+#             */
/*   Updated: 2025/06/11 16:44:07 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execution.h"

char	**get_env_arr(t_env *env)
{
	char	**env_arr;
	char	*temp;
	char	*env_value;
	int		i;

	env_arr = malloc(sizeof(*env_arr) * (envlen(env) + 1));
	if (!env_arr)
		return (NULL);
	i = 0;
	while (env)
	{
		temp = ft_strjoin(env->key, "=");
		if (!temp)
			return (NULL);
		env_value = ft_strjoin(temp, env->value);
		free(temp);
		if (!env_value)
			return (NULL);
		env_arr[i] = env_value;
		i++;
		env = env->next;
	}
	env_arr[i] = NULL;
	return (env_arr);
}

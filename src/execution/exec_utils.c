<<<<<<< HEAD:execution/exec_utils.c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 20:20:28 by michoi            #+#    #+#             */
/*   Updated: 2025/05/11 20:24:30 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execution.h"

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
=======
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 20:20:28 by michoi            #+#    #+#             */
/*   Updated: 2025/06/07 14:49:38 by michoi           ###   ########.fr       */
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
>>>>>>> 874a9b48f3199909f568ebc8744a2ebc01ae86ce:src/execution/exec_utils.c

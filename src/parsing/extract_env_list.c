/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_env_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 12:40:01 by hvahib            #+#    #+#             */
/*   Updated: 2025/06/07 14:51:09 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_env	*process_env_vars(t_env *env_list, char **envp, int env_count)
{
	t_env	*current;
	char	**temp;
	int		i;

	current = env_list;
	i = 0;
	while (i < env_count)
	{
		temp = ft_split(envp[i], '=');
		if (!temp)
			return (free_array(&temp), cleanup_env(env_list), NULL);
		current->key = ft_strdup(temp[0]);
		current->value = ft_strdup(temp[1]);
		free_array(&temp);
		if (!current->key || !current->value)
			return (cleanup_env(env_list), NULL);
		current = current->next;
		i++;
	}
	return (env_list);
}

t_env	*extract_env_list(char **envp)
{
	t_env	*env_list;
	int		env_count;

	env_count = arrlen(envp);
	if (env_count == 0)
		env_list = create_env_list(3);
	else
		env_list = create_env_list(env_count);
	if (!env_list)
		return (printf("env list creation failed\n"), NULL);
	return (process_env_vars(env_list, envp, env_count));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_utility.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 12:39:07 by hvahib            #+#    #+#             */
/*   Updated: 2025/06/11 17:12:13 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_env	*cleanup_env(t_env *env_list)
{
	t_env	*temp;

	temp = NULL;
	while (env_list)
	{
		temp = env_list->next;
		if (env_list->key)
			free(env_list->key);
		if (env_list->value)
			free(env_list->value);
		if (env_list)
			free(env_list);
		env_list = temp;
	}
	free(temp);
	return (env_list);
}

void	clean_out_all(t_env *env1, t_env *env2, char *str1, char *str2)
{
	if (env1)
		cleanup_env(env1);
	if (env2)
		cleanup_env(env2);
	if (str1)
		free(str1);
	if (str2)
		free(str2);
	if (signal(SIGINT, SIG_DFL) == SIG_ERR)
		exit(1);
	if (signal(SIGQUIT, SIG_DFL) == SIG_ERR)
		exit(1);
	if (change_mode(RUNNING_COMMAND))
		exit(1);
}

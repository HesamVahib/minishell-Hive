/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 12:39:20 by hvahib            #+#    #+#             */
/*   Updated: 2025/06/11 16:41:16 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_env	*update_env(t_env *env_list, char *key, char *value)
{
	t_env	*new;
	t_env	*temp;

	if (!key)
		return (NULL);
	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = key;
	new->value = value;
	new->next = NULL;
	if (!env_list->next)
	{
		env_list->next = new;
	}
	else
	{
		temp = env_list;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
	return (env_list);
}

t_env	*node_finder(t_env *env_list, char *key)
{
	t_env	*temp;

	temp = env_list;
	while (temp)
	{
		if (is_same_value(temp->key, key))
			return (temp);
		temp = temp->next;
	}
	return (temp);
}

static void	update_existing_node(t_env *temp, char *value, t_env *env_list)
{
	if (temp->value)
	{
		free(temp->value);
		temp->value = NULL;
	}
	if (value && *value)
	{
		temp->value = ft_strdup(value);
		if (!temp->value)
			clean_out_all(env_list, NULL, NULL, NULL);
	}
}

static t_env	*add_new_node(t_env *env_list, char *key, char *value)
{
	char	*temp_key;
	char	*temp_value;

	temp_value = NULL;
	temp_key = ft_strdup(key);
	if (!temp_key)
		clean_out_all(env_list, NULL, NULL, NULL);
	if (value && *value)
	{
		temp_value = ft_strdup(value);
		if (!temp_value)
			clean_out_all(env_list, NULL, NULL, NULL);
	}
	env_list = update_env(env_list, temp_key, temp_value);
	if (!env_list)
		clean_out_all(env_list, NULL, NULL, NULL);
	return (env_list);
}

t_env	*custom_export(t_env *env_list, char *key, char *value)
{
	t_env	*temp;

	temp = node_finder(env_list, key);
	if (temp)
	{
		update_existing_node(temp, value, env_list);
		return (env_list);
	}
	else
		return (add_new_node(env_list, key, value));
}

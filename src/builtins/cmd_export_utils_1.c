/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export_utils_1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 21:42:13 by michoi            #+#    #+#             */
/*   Updated: 2025/06/14 00:53:32 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

static t_env	*clone_env_node(t_env *env)
{
	t_env	*env_node_copy;

	if (!env)
		return (NULL);
	env_node_copy = malloc(sizeof(t_env));
	if (!env_node_copy)
		return (NULL);
	env_node_copy->key = ft_strdup(env->key);
	env_node_copy->value = ft_strdup(env->value);
	env_node_copy->next = NULL;
	return (env_node_copy);
}

static t_env	*clone_env_list(t_env *env)
{
	t_env	*head;
	t_env	*cur;
	t_env	*new_env;

	if (!env)
		return (NULL);
	head = clone_env_node(env);
	if (!head)
		return (NULL);
	env = env->next;
	cur = head;
	while (env)
	{
		new_env = clone_env_node(env);
		if (!new_env)
		{
			cleanup_env(head);
			return (NULL);
		}
		cur->next = new_env;
		cur = new_env;
		env = env->next;
	}
	return (head);
}

static bool	swap_env_node(t_env **env_ref, t_env **head, t_env **prev)
{
	t_env	*cur;
	t_env	*next;

	cur = *env_ref;
	next = cur->next;
	if (ft_strcmp(cur->key, next->key) > 0)
	{
		cur->next = next->next;
		next->next = cur;
		if (*prev)
			(*prev)->next = next;
		else
			*head = next;
		*prev = next;
		return (true);
	}
	*prev = cur;
	*env_ref = cur->next;
	return (false);
}

static int	sort_env_list(t_env **env_ref)
{
	bool	swapped;
	t_env	*prev;
	t_env	*head;
	t_env	*next;

	if (!env_ref || !*env_ref)
		return (FAILURE);
	head = *env_ref;
	swapped = true;
	while (swapped)
	{
		swapped = false;
		(*env_ref) = head;
		prev = NULL;
		while ((*env_ref)->next)
		{
			next = (*env_ref)->next;
			if (swap_env_node(env_ref, &head, &prev))
				swapped = true;
		}
	}
	*env_ref = head;
	return (SUCCESS);
}

t_env	*get_sorted_env(t_env *env)
{
	t_env	*env_copy;

	env_copy = clone_env_list(env);
	if (!env_copy)
		return (NULL);
	if (sort_env_list(&env_copy))
	{
		if (env)
			cleanup_env(env);
		return (NULL);
	}
	return (env_copy);
}

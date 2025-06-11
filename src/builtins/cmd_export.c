/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 21:47:21 by michoi            #+#    #+#             */
/*   Updated: 2025/06/11 17:32:19 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

t_env	*clone_env_node(t_env *env)
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

t_env	*clone_env_list(t_env *env)
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

void	sort_export_list(t_env **env_ref)
{
	bool	swapped;
	t_env	*prev;
	t_env	*head;
	t_env	*next;

	if (!env_ref || !*env_ref)
		return ;
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
			if (ft_strcmp((*env_ref)->key, next->key) > 0)
			{
				(*env_ref)->next = next->next;
				next->next = *env_ref;
				swapped = true;
				if (prev)
					prev->next = next;
				else
					head = next;
				prev = next;
			}
			else
			{
				prev = (*env_ref);
				*env_ref = (*env_ref)->next;
			}
		}
	}
	*env_ref = head;
}

// number, underscore, alphabets
static bool	is_right_key_name(char *key)
{
	if (!key || !*key)
		return (false);
	if (!ft_isalpha(*key) && *key != '_')
		return (false);
	key++;
	while (*key && *key != '=')
	{
		if (!ft_isdigit(*key) && !ft_isalpha(*key) && *key != '_')
			return (false);
		key++;
	}
	return (true);
}

static void	print_export_list(t_env *env)
{
	t_env	*env_copy;
	t_env	*env_copy_head;

	if (!env)
	{
		ft_putendl_fd("env list is empty", STDERR_FILENO);
		return ;
	}
	env_copy = clone_env_list(env);
	if (!env_copy)
		return ;
	sort_export_list(&env_copy);
	if (!env_copy)
		return ;
	env_copy_head = env_copy;
	while (env_copy)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(env_copy->key, STDOUT_FILENO);
		if (env_copy->value)
		{
			ft_putstr_fd("=\"", STDOUT_FILENO);
			ft_putstr_fd(env_copy->value, STDOUT_FILENO);
			ft_putendl_fd("\"", STDOUT_FILENO);
		}
		else
			ft_putchar_fd('\n', STDOUT_FILENO);
		env_copy = env_copy->next;
	}
	cleanup_env(env_copy_head);
}

static int	check_key_name(char *arg)
{
	if (!is_right_key_name(arg))
	{
		ft_putstr_fd("(what the)shell: ", STDERR_FILENO);
		ft_putstr_fd("export: `", STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
		return (FAILURE);
	}
	return (SUCCESS);
}

static int	get_key_idx(char *arg)
{
	int	key_index;

	key_index = get_idx(arg, '=');
	if (key_index == -1)
		key_index = ft_strlen(arg);
	return (key_index);
}

static int	export_key_value(char *arg, t_env *env)
{
	char	*key;
	char	*value;
	int		key_index;

	value = NULL;
	key_index = get_key_idx(arg);
	key = ft_substr(arg, 0, key_index);
	if (!key)
	{
		ft_putendl_fd("export: failed to get key", STDERR_FILENO);
		return (FAILURE);
	}
	if (arg[key_index] == '=')
	{
		value = ft_substr(arg, key_index + 1, ft_strlen(arg) - key_index - 1);
		if (!value)
		{
			ft_putendl_fd("export: failed to get value", STDERR_FILENO);
			return (free(key), FAILURE);
		}
	}
	custom_export(env, key, value);
	free(key);
	free(value);
	return (SUCCESS);
}

int	cmd_export(t_env *env, char **args)
{
	t_env	*temp_env;
	
	temp_env = env;
	if (!args || !*args)
	{
		print_export_list(temp_env);
		return (SUCCESS);
	}
	while (*args)
	{
		if (check_key_name(*args))
			return (FAILURE);
		if (export_key_value(*args, env))
			return (FAILURE);
		args++;
	}
	return (SUCCESS);
}

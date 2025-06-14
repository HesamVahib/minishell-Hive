/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 21:47:21 by michoi            #+#    #+#             */
/*   Updated: 2025/06/11 22:08:13 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

static int	print_export_list(t_env *env)
{
	t_env	*sorted_env;
	t_env	*sorted_env_head;

	if (!env)
	{
		ft_putendl_fd("env list is empty", STDERR_FILENO);
		return (FAILURE);
	}
	sorted_env = get_sorted_env(env);
	if (!sorted_env)
	{
		ft_putendl_fd("failed to sort env list", STDERR_FILENO);
		return (FAILURE);
	}
	sorted_env_head = sorted_env;
	while (sorted_env)
	{
		print_key_value(sorted_env);
		sorted_env = sorted_env->next;
	}
	cleanup_env(sorted_env_head);
	return (SUCCESS);
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

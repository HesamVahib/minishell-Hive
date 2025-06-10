/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 21:47:21 by michoi            #+#    #+#             */
/*   Updated: 2025/05/25 20:27:05 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"

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
	if (!env)
		return ;
	// sort_export_list(&env);
	while (env)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(env->key, STDOUT_FILENO);
		if (env->value)
		{
			ft_putstr_fd("=\"", STDOUT_FILENO);
			ft_putstr_fd(env->value, STDOUT_FILENO);
			ft_putendl_fd("\"", STDOUT_FILENO);
		}
		else
			ft_putchar_fd('\n', STDOUT_FILENO);
		env = env->next;
	}
}
int	get_idx(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

static int	check_key_name(char *arg)
{
	if (!is_right_key_name(arg))
	{
		ft_putstr_fd("(what the)shell: ", STDERR_FILENO);
		ft_putstr_fd("export: `", STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
		return (FAILURE); // exit 1
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
			return (FAILURE); // exit 1
		// split with =
		if (export_key_value(*args, env))
			return (FAILURE);
		// printf("key: %s, val: %s idx: %d\n", key, value, key_index);
		args++;
	}
	// exit code 127 --> what was that :D
	return (SUCCESS);
}

/*
michoi@c3r2p7:~$ export abc = hi n = 123
bash: export: `=': not a valid identifier
bash: export: `=': not a valid identifier
bash: export: `123': not a valid identifier
declare -x a="123"
declare -x abc
declare -x b="234"
declare -x hi
declare -x n="0"

*/
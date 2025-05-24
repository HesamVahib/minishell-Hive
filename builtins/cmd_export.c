/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 21:47:21 by michoi            #+#    #+#             */
/*   Updated: 2025/05/25 01:07:34 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"

// number, underscore, alphabets
static bool	is_right_key_name(char *key)
{
	if (!key || !*key)
		return (false);
	if (!ft_isalpha(*key) && *key != '_')
	{
		printf("is false: %d, %d", !ft_isalpha(*key), *key != '_');
		return (false);
	}
	key++;
	while (*key && *key != '=')
	{
		if (!ft_isdigit(*key) && !ft_isalpha(*key) && *key != '_')
			return (false);
		key++;
	}
	return (true);
}

// t_env	*export_with_null(t_env *env_list, char *key, char *value)
// {
// 	t_env	*temp;
// 	char	*temp_key;
// 	char	*temp_value;

// 	temp_value = NULL;
// 	temp = node_finder(env_list, key);
// 	if (temp)
// 	{
// 		if (temp->value)
// 			free(temp->value);
// 		if (value && *value)
// 		{
// 			temp->value = ft_strdup(value);
// 			if (!temp->value)
// 				clean_out_all(env_list, NULL, NULL, NULL);
// 		}
// 		return (env_list);
// 	}
// 	else
// 	{
// 		temp_key = ft_strdup(key);
// 		if (!temp_key)
// 			clean_out_all(env_list, NULL, NULL, NULL);
// 		if (value && *value)
// 		{
// 			temp_value = ft_strdup(value);
// 			if (!temp_value)
// 				clean_out_all(env_list, NULL, NULL, NULL);
// 		}
// 		env_list = update_env(env_list, temp_key, temp_value);
// 		if (!env_list)
// 			clean_out_all(env_list, NULL, NULL, NULL);
// 		return (env_list);
// 	}
// }

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

int	cmd_export(t_env **env, char **args)
{
	t_env	**temp_env;
	char	*key;
	char	*value;
	int		key_index;

	value = NULL;
	temp_env = env;
	if (!args || !*args)
	{
		print_export_list(*temp_env);
		return (SUCCESS);
	}
	while (*args)
	{
		if (!is_right_key_name(*args))
		{
			ft_putstr_fd("(what the)shell: ", STDERR_FILENO);
			ft_putstr_fd("export: `", STDERR_FILENO);
			ft_putstr_fd(*args, STDERR_FILENO);
			ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
			return (FAILURE); // exit 1
		}
		// split with =
		key_index = get_idx(*args, '=');
		if (key_index == -1)
			key_index = ft_strlen(*args);
		key = ft_substr(*args, 0, key_index);
		if (!key)
		{
			ft_putendl_fd("export: failed to get key", STDERR_FILENO);
			return (FAILURE);
		}
		if ((*args) + (key_index + 1) != NULL)
		{
			value = ft_substr(*args, key_index + 1, ft_strlen(*args));
			if (!value)
			{
				ft_putendl_fd("export: failed to get value", STDERR_FILENO);
				return (FAILURE);
			}
		}
		printf("key: %s, val: %s idx: %d\n", key, value, key_index);
		// // free key and val
		custom_export(*env, key, value);
		free(key);
		free(value);
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
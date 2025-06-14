/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export_utils_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 21:47:42 by michoi            #+#    #+#             */
/*   Updated: 2025/06/11 22:04:42 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

// number, underscore, alphabets
bool	is_right_key_name(char *key)
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

int	get_key_idx(char *arg)
{
	int	key_index;

	key_index = get_idx(arg, '=');
	if (key_index == -1)
		key_index = ft_strlen(arg);
	return (key_index);
}

void	print_key_value(t_env *env)
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
}

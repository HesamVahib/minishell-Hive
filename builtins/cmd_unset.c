/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 21:47:18 by michoi            #+#    #+#             */
/*   Updated: 2025/05/10 23:09:32 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"

/*
bool	is_option(char *arg)
{
	int	i;

	if (!arg || !*arg)
		return (false);
	i = 0;
	if (arg[i] == '-' || arg[i] == '-' && arg[i + 1] == '-')
	return (false);
}
*/

// ~ no options!!! ~
int	cmd_unset(t_env **env, char **args)
{
	t_env	*node;

	if (!args || !*args)
		return (SUCCESS);
	while (*args)
	{
		node = node_finder(*env, *args);
		if (node)
			remove_node(*env, node);
		args++;
	}
	// if (is_option(*args))
	// 	return (FAILURE);
	return (SUCCESS);
}

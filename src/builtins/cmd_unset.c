/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 21:47:18 by michoi            #+#    #+#             */
/*   Updated: 2025/06/09 18:09:12 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

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
	return (SUCCESS);
}

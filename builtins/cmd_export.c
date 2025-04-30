/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 21:47:21 by michoi            #+#    #+#             */
/*   Updated: 2025/04/30 20:12:12 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"

void	sort_export_list(t_env **env)
{
	t_env	*head;
	t_env	*node;
	t_env	*temp;
	bool	swapped;

	head = *env;
	node = *env;
	swapped = false;
	while (!swapped)
	{
		while (node->next->next)
		{
			if (node->key > node->next->key)
			{
				temp = node;
				temp->next = node->next->next;
				node = node->next;
				node->next = temp;
				swapped = true;
			}
			node = node->next;
		}
	}
}

void	print_export_list(t_env *env)
{
	t_env	*temp_env;

	temp_env = env;
	sort_export_list(&temp_env);
	while (temp_env)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(temp_env->key, STDOUT_FILENO);
		if (temp_env->value)
		{
			ft_putstr_fd("=\"", STDOUT_FILENO);
			ft_putstr_fd(temp_env->value, STDOUT_FILENO);
			ft_putendl_fd("\"", STDOUT_FILENO);
		}
		else
			ft_putchar_fd('\n', STDOUT_FILENO);
		temp_env = temp_env->next;
	}
}

int	cmd_export(t_env **env, char **args)
{
	// if (*args) return error?
	if (!args || !*args)
		print_export_list(*env);
	return (SUCCESS);
}

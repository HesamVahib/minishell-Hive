/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 21:47:21 by michoi            #+#    #+#             */
/*   Updated: 2025/05/10 21:56:43 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"

// void	sort_export_list(t_env **env)
// {
// 	t_env	*head;
// 	t_env	*former;
// 	t_env	*latter;
// 	bool	swapped;

// 	head = *env;
// 	former = *env;

// 	while (!swapped)
// 	{
// 		swapped = false;
// 		while (former->next)
// 		{
// 			latter = former->next;
// 			if (ft_strcmp(former->key, latter->key))
// 			{
// 				former->next = latter->next;
// 				latter->next = former;
// 				if (former == head)
// 					head = latter;
// 			}
// 			former = former->next;
// 		}
// 	}
// }

void	print_export_list(t_env *env)
{
	if (!env)
		return (ft_putendl_fd("print export list error", STDERR_FILENO));
	//sort_export_list(&env);

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

int	cmd_export(t_env **env, char **args)
{
	t_env **temp_env;

	temp_env = env;
	if (!args || !*args)
	{
		print_export_list(*temp_env);
		return (SUCCESS);
	}
	// if (*args) return error?
	if (!ft_strncmp("-", *args, ft_strlen(*args)))
	{
		ft_putstr_fd("(what the)shell: ", STDERR_FILENO);
		ft_putstr_fd("export: `", STDERR_FILENO);
		ft_putstr_fd(*args, STDERR_FILENO);
		ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
		return (FAILURE); // exit 1
	}
	// exit code 127 --> what was that :D
	return (SUCCESS);
}

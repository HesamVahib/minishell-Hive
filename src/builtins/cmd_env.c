/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 21:47:16 by michoi            #+#    #+#             */
/*   Updated: 2025/06/09 21:06:37 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

/**
 * Print out a set of current environment variables.

	* @param env: current list of environment variables
	* @param args: are forbidden and
					the function will throw an error when it's provided.
	* @return
		SUCCESS - Operation completed successfully.
		FAILURE - Operation failed due to an error.
 */
int	cmd_env(t_env *env, char **args)
{
	if (args && *args)
	{
		ft_putstr_fd("env : ‘", STDERR_FILENO);
		ft_putstr_fd(*args, STDERR_FILENO);
		ft_putendl_fd("’: No such file or directory", STDERR_FILENO);
		return (127);
	}
	while (env)
	{
		if (env->value && (*env->value))
		{
			ft_putstr_fd(env->key, STDOUT_FILENO);
			ft_putchar_fd('=', STDOUT_FILENO);
			ft_putendl_fd(env->value, STDOUT_FILENO);
		}
		// else
		// {
		// 	printf("env value: %s\n", env->value);
		// 	ft_putstr_fd(env->key, STDOUT_FILENO);
		// 	// ft_putendl_fd("=", STDOUT_FILENO);
		// }
		env = env->next;
	}
	return (SUCCESS);
}

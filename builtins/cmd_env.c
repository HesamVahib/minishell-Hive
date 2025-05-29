/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 21:47:16 by michoi            #+#    #+#             */
/*   Updated: 2025/05/27 20:09:27 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"

/**
 * Print out a set of current environment variables.

	* @param env: current list of environment variables (should be replaced with the minishell struct later?)

	* @param args: are forbidden but the function will throw an error when it's provided.
	* @return
		SUCCESS - Operation completed successfully.

		FAILURE - Operation failed due to an error.
 */
int	cmd_env(t_env *env, char **args)
{
	int	i;

	i = 0;
	if (*args)
	{
		ft_putstr_fd("env : ‘", STDERR_FILENO);
		ft_putstr_fd( *args, STDERR_FILENO);
		ft_putendl_fd("’: No such file or directory", STDERR_FILENO);
		return (127); // exit code 127
	}
	while (env)
	{
		// don't print keys which don't have value!!!!
		if (env->value)
		{
			ft_putstr_fd(env->key, STDOUT_FILENO);
			ft_putchar_fd('=', STDOUT_FILENO);
			ft_putendl_fd(env->value, STDOUT_FILENO);
		}
		env = env->next;
		i++;
	}
	return (SUCCESS);
}

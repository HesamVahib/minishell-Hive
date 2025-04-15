/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvahib <hvahib@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 21:47:16 by michoi            #+#    #+#             */
/*   Updated: 2025/04/15 18:08:44 by hvahib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"

/**
 * Print out a set of current environment variables.
 * @param env: current list of environment variables (should be replaced with the minishell struct later?)
 * @param args: args are forbidden but the function will throw an error when it's provided.
 * @return
		SUCCESS - Operation completed successfully.

		FAILURE - Operation failed due to an error.
 */
int	env(t_env *env, char **args)
{
	// Do we have to handle the situation when args are provided?
	if (*args)
	{
		ft_putstr_fd("env: ‘", STDERR_FILENO);
		ft_putstr_fd(*args, STDERR_FILENO);
		ft_putendl_fd("‘: No such file or directory", STDERR_FILENO);
		//exit code 127
		return (FAILURE);
	}
	while (env)
	{
		ft_putstr_fd(env->key, STDOUT_FILENO);
		ft_putchar_fd("=", STDOUT_FILENO);
		ft_putendl_fd(env->value, STDOUT_FILENO);
		env = env->next;
	}
	return (SUCCESS);
}

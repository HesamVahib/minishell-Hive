/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 21:47:16 by michoi            #+#    #+#             */
/*   Updated: 2025/04/16 14:22:57 by michoi           ###   ########.fr       */
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
int	cmd_env(t_env *env, char **args)
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


t_env	*extract_env_list(char **envp)
{
	t_env	*env_list;
	int		i;
	int		env_count;
	char	**temp;
	t_env	*temp_env;

	env_count = arrlen(envp);
		// function to count the number of environment variables
	env_list = create_env_list(env_count);
		// function to create an empty environment list
	if (!env_list)
		return (printf("env_list is null"), NULL);
			// handle error if create_env_list fails
	i = 0;
	temp_env = env_list;
	// printf("testhi: %s\n", temp_env->key);
	while (i < env_count)
	{
		temp = ft_split(envp[i], '=');
			// function to split the environment variable into key and value
		if (!temp)
			return (cleanup_env(env_list), NULL);
		temp_env->key = ft_strdup(temp[0]);
		temp_env->value = ft_strdup(temp[1]);
		// clean_array(temp);
		if (!temp_env->key || !temp_env->value)
			return (cleanup_env(env_list), NULL);
		// *(temp_env->index) = i;
		temp_env = temp_env->next;
		i++;
	}
	// env_list = temp_env;
	// while (env_list)
	// {
	//     // printf("%s, %s\n", env_list->key, env_list->value);
	//     env_list = env_list->next;
	// }
	// exit (1);
	return (env_list);
}

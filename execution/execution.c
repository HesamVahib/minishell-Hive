/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 22:01:29 by michoi            #+#    #+#             */
/*   Updated: 2025/05/10 18:43:06 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool	is_in_array(const char **arr, char *s)
{
	if (!arr || !*arr)
		return (false);
	while (*arr)
	{
		if (!ft_strncmp(*arr, s, ft_strlen(s)))
			return (true);
		arr++;
	}
	return (false);
}

char	**split_env_path(t_env *env)
{
	char	*path;

	if (!env)
		return (NULL);
	path = find_value_from_env(env, "PATH");
	if (!path || !*path)
		return (NULL);
	return (ft_split(path, ':'));
}

char	*get_cmd_path(t_env *env, char *cmd)
{
	char	**paths;
	char	*exec_path;
	char	*cmd_with_slash;
	int		i;

	if (!env || !cmd || !*cmd)
		return (NULL);
	if (!access(cmd, F_OK | X_OK))
		return (cmd);
	paths = split_env_path(env);
	if (!paths)
		return (NULL);
	cmd_with_slash = ft_strjoin("/", cmd);
	if (!cmd_with_slash)
		return (free_array(&paths), NULL);
	i = 0;
	while (paths[i])
	{
		exec_path = ft_strjoin(paths[i], cmd_with_slash);
		if (exec_path && !(access(exec_path, F_OK | X_OK)))
			return (free_array(&paths), free(cmd_with_slash), exec_path);
		free(exec_path);
		i++;
	}
	return (free_array(&paths), free(cmd_with_slash), NULL);
}

int	envlen(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

char	**get_env_arr(t_env *env)
{
	char	**env_arr;
	char	*temp;
	char	*env_value;
	int		i;

	env_arr = malloc(sizeof(*env_arr) * (envlen(env) + 1));
	if (!env_arr)
		return (NULL);
	i = 0;
	while (env)
	{
		temp = ft_strjoin(env->key, "=");
		if (!temp)
			return (NULL);
		env_value = ft_strjoin(temp, env->value);
		free(temp);
		if (!env_value)
			return (NULL);
		env_arr[i] = env_value;
		i++;
		env = env->next;
	}
	env_arr[i] = NULL;
	return (env_arr);
}

int	exec_cmd(t_cmd *cmd_args, t_env *env)
{
	t_cp		cp;
	pid_t		child_pid;
	int			wait_stat;
	bool		is_piped_already;
	const char	*builtins[] = {CMD_CD, CMD_ECHO, CMD_ENV, CMD_EXPORT, CMD_PWD,
			CMD_UNSET, NULL};
	char		**env_arr;

	is_piped_already = false;
	// open_create_files


	// while (cmd_args->argv)
	// {
	// 	printf("%s\n", *(cmd_args->argv));
	// 	(cmd_args->argv)++;
	// }

	while (cmd_args)
	{
		// if there's only one cmd (no pipe)
		if (!is_piped_already && !cmd_args->is_piped)
		{
			// builtin
			if (is_in_array(builtins, cmd_args->argv[0]))
			{
				// call_builtin
				if (exec_builtin(env, cmd_args->argv[0], cmd_args->argv + 1))
					return (FAILURE);
			}
			else
			{
				// fork
				child_pid = fork();
				if (child_pid == -1)
				{
					perror("Fork failed");
					return (FAILURE);
				}
				if (child_pid == 0)
				{
					env_arr = get_env_arr(env);
					// close file?
					if (!env_arr)
						exit(EXIT_FAILURE);
					cp.path = get_cmd_path(env, cmd_args->argv[0]);
					cp.args = cmd_args->argv;
					if (!cp.path)
					{
						free_array(&env_arr);
						exit(EXIT_FAILURE);
						// close file
					}
					// execve
					if (execve(cp.path, cp.args, env_arr))
					{
						free(cp.path);
						free_array(&env_arr);
						perror("execve failed");
						exit(EXIT_FAILURE);
						//close file
					}
				}
				if (waitpid(child_pid, &wait_stat, 0) == -1)
					return (FAILURE);
			}
		}
		else
		{
			//	is_piped_already = true;
		}
		cmd_args = cmd_args->next;
	}
	return (SUCCESS);
}

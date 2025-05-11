/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 20:19:41 by michoi            #+#    #+#             */
/*   Updated: 2025/05/11 20:25:02 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execution.h"

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

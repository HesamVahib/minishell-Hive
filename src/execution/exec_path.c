/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 20:19:41 by michoi            #+#    #+#             */
/*   Updated: 2025/06/09 21:14:54 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execution.h"

void	print_path_err(t_cmd *cmd)
{
	if (errno == EACCES || errno == ENOENT || errno == EISDIR)
		print_cmd_err(cmd->argv[0], strerror(errno));
	else
		print_basic_error(cmd->argv[0], "command not found");
}

int	set_path_exit_code(int err_no)
{
	int	code;

	if (err_no == EACCES || err_no == EISDIR)
		code = 126;
	else
		code = 127;
	return (code);
}

/**
 * 1. Is a directory: 126
 * 2. Permission denied: 126
 * 3. cmd not found: 127
 */
static char	*validate_cmd_path(char *cmd_path)
{
	struct stat	sb;

	if (!stat(cmd_path, &sb))
	{
		if (S_ISDIR(sb.st_mode))
		{
			errno = EISDIR;
			return (NULL);
		}
		if (access(cmd_path, X_OK))
			return (NULL);
		return (cmd_path);
	}
	else
		return (NULL);
}

static char	**split_env_path(t_env *env)
{
	char	*path;

	if (!env)
		return (NULL);
	path = find_value_from_env(env, "PATH");
	if (!path || !*path)
		return (NULL);
	return (ft_split(path, ':'));
}

/*
- path without / -> command not found +
- ./path -> Is a directory +
- file -> permission denied +
- wrong file path:  No such file or directory +
 */
char	*get_cmd_path(t_env *env, char *cmd)
{
	char	**paths;
	char	*exec_path;
	char	*cmd_with_slash;
	int		i;

	if (!env || !cmd || !*cmd)
		return (NULL);
	if (ft_strchr(cmd, '/'))
		return (validate_cmd_path(cmd));
	paths = split_env_path(env);
	if (!paths)
		return (NULL);
	cmd_with_slash = ft_strjoin("/", cmd);
	if (!cmd_with_slash)
		return (free_array(&paths), NULL);
	i = 0;
	while (paths[i])
	{
		exec_path = ft_strjoin(paths[i++], cmd_with_slash);
		if (exec_path && !(access(exec_path, F_OK | X_OK)))
			return (free_array(&paths), free(cmd_with_slash), exec_path);
		free(exec_path);
	}
	errno = 0;
	return (free_array(&paths), free(cmd_with_slash), NULL);
}

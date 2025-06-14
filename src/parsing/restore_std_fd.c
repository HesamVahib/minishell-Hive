/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   restore_std_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 12:42:18 by hvahib            #+#    #+#             */
/*   Updated: 2025/06/11 18:17:36 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	restore_fd(t_env_pack env_pack, int std_fd, char *key)
{
	char	*fd;
	int		cur_fd;

	fd = find_value_from_env(env_pack.mshell_env, key);
	if (fd)
	{
		cur_fd = ft_atoi(fd);
		if (cur_fd >= 0)
		{
			if (std_fd != STDIN_FILENO)
				if (close(std_fd) == -1)
					clean_out_all(env_pack.mshell_env, env_pack.sys_envlist,
						NULL, NULL);
			if (dup2(cur_fd, std_fd) == -1)
				clean_out_all(env_pack.mshell_env, env_pack.sys_envlist, NULL,
					NULL);
			if (close(cur_fd) == -1)
				clean_out_all(env_pack.mshell_env, env_pack.sys_envlist,
					NULL, NULL);
		}
	}
}

void	restore_std_fd(t_env_pack env_pack)
{
	restore_fd(env_pack, STDIN_FILENO, "fd_stdin");
	restore_fd(env_pack, STDOUT_FILENO, "fd_stdout");
	restore_fd(env_pack, STDERR_FILENO, "fd_stderr");
}

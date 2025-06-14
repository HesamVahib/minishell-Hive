/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_export_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 12:39:20 by hvahib            #+#    #+#             */
/*   Updated: 2025/06/11 16:41:16 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static	t_env_pack	std_fd_custom_exporter(t_env_pack env_pack,
											int fd_std, char *key)
{
	char	*std_itoa;
	int		fd;

	fd = dup(fd_std);
	if (fd == -1)
		clean_out_all(env_pack.sys_envlist, env_pack.mshell_env, NULL, NULL);
	std_itoa = ft_itoa(fd);
	if (!std_itoa)
		clean_out_all(env_pack.sys_envlist, env_pack.mshell_env, NULL, NULL);
	env_pack.mshell_env = custom_export(env_pack.mshell_env, key, std_itoa);
	free(std_itoa);
	return (env_pack);
}

t_env_pack	export_std_fd(t_env_pack env_pack)
{
	env_pack = std_fd_custom_exporter(env_pack, STDIN_FILENO, "fd_stdin");
	env_pack = std_fd_custom_exporter(env_pack, STDOUT_FILENO, "fd_stdout");
	env_pack = std_fd_custom_exporter(env_pack, STDERR_FILENO, "fd_stderr");
	return (env_pack);
}

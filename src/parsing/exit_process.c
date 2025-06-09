/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 12:39:47 by hvahib            #+#    #+#             */
/*   Updated: 2025/06/09 21:33:31 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	exit_run(t_env *env)
{
	int	fd;
	
	fd = ft_atoi(find_value_from_env(env, "fd_stdin"));
	if (fd > 2)
		close(fd);
	fd = ft_atoi(find_value_from_env(env, "fd_stdout"));
	if (fd > 2)
		close(fd);
	fd = ft_atoi(find_value_from_env(env, "fd_stderr"));
	if (fd > 2)
		close(fd);
	if (signal(SIGINT, SIG_DFL) == SIG_ERR)
		exit(1);
	if (signal(SIGQUIT, SIG_DFL) == SIG_ERR)
		exit(1);
	if (change_mode(RUNNING_COMMAND))
		exit(1);
}

void	exit_preparation(t_env_pack env_pack)
{
	int	exit_code;
	
	ft_putendl_fd("exit", STDERR_FILENO);
	exit_code = set_and_get_exit_status(0, false);
	// cleanup_env(env_pack.sys_envlist);
	exit_run(env_pack.mshell_env);
	clean_out_all(env_pack.mshell_env, env_pack.sys_envlist, NULL, NULL);
	exit(exit_code);
}

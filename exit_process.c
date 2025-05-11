/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvahib <hvahib@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 12:39:47 by hvahib            #+#    #+#             */
/*   Updated: 2025/05/08 13:38:20 by hvahib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void	exit_run(t_env *env)
{
	int	exit_code;

	printf("exit\n");
	exit_code = ft_atoi(find_value_from_env(env, "exit_code"));
	cleanup_env(env);
	if (signal(SIGINT, SIG_DFL) == SIG_ERR)
		exit(1);
	if (signal(SIGQUIT, SIG_DFL) == SIG_ERR)
		exit(1);
	if (change_mode(RUNNING_COMMAND))
		exit(1);
	exit(exit_code);
}

void	exit_preparation(t_env_pack env_pack)
{
	cleanup_env(env_pack.sys_envlist);
	exit_run(env_pack.mshell_env);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env_pack.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 12:40:34 by hvahib            #+#    #+#             */
/*   Updated: 2025/06/11 19:06:14 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	setup_minishell_env(t_env **minishell_env_list, char *cur_dir)
{
	*minishell_env_list = custom_export(*minishell_env_list, "fd_stdin",
			FD_UNSET);
	*minishell_env_list = custom_export(*minishell_env_list, "fd_stdout",
			FD_UNSET);
	*minishell_env_list = custom_export(*minishell_env_list, "fd_stderr",
			FD_UNSET);
	*minishell_env_list = custom_export(*minishell_env_list, "root", cur_dir);
}

static void	add_special_vars(t_env **minishell_env_list)
{
	char	*init_pid;
	char	*temp;

	init_pid = init_getpid();
	temp = ft_itoa(0);
	if (!init_pid)
		clean_out_all(NULL, *minishell_env_list, NULL, NULL);
	*minishell_env_list = custom_export(*minishell_env_list, "pid", init_pid);
	free(temp);
	free(init_pid);
}

static void	handle_empty_env(t_env **minishell_env_list, char *cur_dir)
{
	custom_export(*minishell_env_list, "PWD", cur_dir);
	if (find_value_from_env(*minishell_env_list, "SHLVL"))
	{
		custom_export(*minishell_env_list, "SHLVL", "2");
		printf("HERE\n");
	}
	else
		custom_export(*minishell_env_list, "SHLVL", "1");
	custom_export(*minishell_env_list, "_", "/usr/bin/env");
}

static void	handle_non_empty_env(t_env **minishell_env_list, char *cur_dir)
{
	setup_minishell_env(minishell_env_list, cur_dir);
	add_special_vars(minishell_env_list);
}

t_env_pack	init_env_pack(char **envp, char *cur_dir)
{
	t_env_pack	env_pack;
	t_env		*env_list;
	t_env		*minishell_env_list;

	if (!cur_dir)
	{
		env_pack.sys_envlist = NULL;
		env_pack.mshell_env = NULL;
		return (env_pack);
	}
	env_list = NULL;
	minishell_env_list = NULL;
	initialize_env_lists(envp, &env_list, &minishell_env_list);
	if (arrlen(envp) > 0)
		handle_non_empty_env(&minishell_env_list, cur_dir);
	else
		handle_empty_env(&minishell_env_list, cur_dir);
	free(cur_dir);
	env_pack.sys_envlist = env_list;
	env_pack.mshell_env = minishell_env_list;
	return (env_pack);
}

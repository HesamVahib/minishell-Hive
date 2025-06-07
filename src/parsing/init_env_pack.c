/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env_pack.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 12:40:34 by hvahib            #+#    #+#             */
/*   Updated: 2025/06/07 14:51:49 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*init_getpid(void)
{
	return (ft_strdup("$$"));
}

static void	initialize_env_lists(char **envp, t_env **sys_envlist,
		t_env **minishell_env_list)
{
	*sys_envlist = extract_env_list(envp);
	if (!*sys_envlist)
		clean_out_all(*sys_envlist, *minishell_env_list, NULL, NULL);
	*minishell_env_list = extract_env_list(envp);
	if (!*sys_envlist)
		clean_out_all(*sys_envlist, *minishell_env_list, NULL, NULL);
	*sys_envlist = set_start(*sys_envlist);
	if (!*sys_envlist)
		clean_out_all(*sys_envlist, *minishell_env_list, NULL, NULL);
}

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
	{
		setup_minishell_env(&minishell_env_list, cur_dir);
		add_special_vars(&minishell_env_list);
	}
	else
	{
		custom_export(minishell_env_list, "PWD", cur_dir);
		if (find_value_from_env(minishell_env_list, "SHLVL"))
			custom_export(minishell_env_list, "SHLVL", "2");
		else
			custom_export(minishell_env_list, "SHLVL", "1");
		custom_export(minishell_env_list, "_", "/usr/bin/env");
	}
	free(cur_dir);
	env_pack.sys_envlist = env_list;
	env_pack.mshell_env = minishell_env_list;
	return (env_pack);
}

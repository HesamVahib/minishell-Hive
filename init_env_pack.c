/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env_pack.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvahib <hvahib@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 12:40:34 by hvahib            #+#    #+#             */
/*   Updated: 2025/05/08 12:40:36 by hvahib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

char	*init_getpid(void)
{
	int		pid;
	char	*char_pid;

	pid = getpid();
	if (pid <= 0)
	{
		char_pid = ft_strdup("$$");
		if (!char_pid)
		{
			return (NULL);
		}
		return (char_pid);
	}
	else
	{
		char_pid = ft_itoa(pid);
		if (!char_pid)
		{
			return (NULL);
		}
		return (char_pid);
	}
}

static void	initialize_env_lists(char **envp, t_env **sys_envlist,
		t_env **minishell_env_list)
{
	*sys_envlist = extract_env_list(envp);
	*minishell_env_list = extract_env_list(envp);
	if (!*sys_envlist || !*minishell_env_list)
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
	*minishell_env_list = custom_export(*minishell_env_list, "exit_code", temp);
	free(temp);
	free(init_pid);
}

t_env_pack	init_env_pack(char **envp, char *cur_dir)
{
	t_env_pack	env_pack;
	t_env		*env_list;
	t_env		*minishell_env_list;

	env_list = NULL;
	minishell_env_list = NULL;
	initialize_env_lists(envp, &env_list, &minishell_env_list);
	setup_minishell_env(&minishell_env_list, cur_dir);
	free(cur_dir);
	add_special_vars(&minishell_env_list);
	env_pack.sys_envlist = env_list;
	env_pack.mshell_env = minishell_env_list;
	return (env_pack);
}

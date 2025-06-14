/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 12:40:34 by hvahib            #+#    #+#             */
/*   Updated: 2025/06/11 19:06:14 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*init_getpid(void)
{
	return (ft_strdup("$$"));
}

void	initialize_env_lists(char **envp, t_env **sys_envlist,
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

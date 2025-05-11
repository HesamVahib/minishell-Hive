/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvahib <hvahib@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 22:01:29 by michoi            #+#    #+#             */
/*   Updated: 2025/05/11 18:10:04 by hvahib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool	is_in_array(const char **arr, char *s)
{
	if (!arr || !*arr)
		return (false);
	while (*arr)
	{
		if (!ft_strncmp(*arr, s, ft_strlen(s)))
			return (true);
		arr++;
	}
	return (false);
}

int	execute_cmd(t_cmd *cmd_args, t_env *env)
{
	const char	*builtins[] = {CMD_CD, CMD_ECHO, CMD_ENV, CMD_EXPORT, CMD_PWD,
		CMD_UNSET, NULL};

	if (!cmd_args)
		return (SUCCESS);
	if (!cmd_args->is_piped)
	{
		if (is_in_array(builtins, cmd_args->argv[0]))
		{
			// call_builtin
			exec_builtin(env, cmd_args->argv[0], cmd_args->argv + 1);
		}
		// else
		// {
		// fork && execve
		// }
	}
	return (SUCCESS);
}

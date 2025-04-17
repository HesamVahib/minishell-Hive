/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 17:22:37 by michoi            #+#    #+#             */
/*   Updated: 2025/04/17 19:10:38 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h";

int	exec_builtin(t_env *env, char *cmd, char **args)
{
	if (!strncmp(cmd, CMD_CD, ft_strlen(cmd)))
	{
		if (cmd_cd(args, env) == FAILURE)
			return (FAILURE);
	}
	else if (!strncmp(cmd, CMD_ECHO, ft_strlen(cmd)))
	{
		if (cmd_echo(args) == FAILURE)
			return (FAILURE);
	}
	else if (!strncmp(cmd, CMD_ENV, ft_strlen(cmd)))
	{
		if (cmd_env(args, env) == FAILURE)
			return (FAILURE);
	}
	else if (!strncmp(cmd, CMD_EXIT, ft_strlen(cmd)))
	{
		if (cmd_exit(args) == FAILURE)
			return (FAILURE);
	}
	else if (!strncmp(cmd, CMD_EXPORT, ft_strlen(cmd)))
	{
		if ((args, env) == FAILURE)
			return (FAILURE);
	}
	else if (!strncmp(cmd, CMD_PWD, ft_strlen(cmd)))
	{
		if (cmd_pwd() == FAILURE)
			return (FAILURE);
	}
	else if (!strncmp(cmd, CMD_UNSET, ft_strlen(cmd)))
	{
		if ((args, env) == FAILURE)
			return (FAILURE);
	}
	else
		return (FAILURE);
	return (SUCCESS);
}

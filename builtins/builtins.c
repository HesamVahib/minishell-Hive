/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 17:22:37 by michoi            #+#    #+#             */
/*   Updated: 2025/05/09 20:21:29 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"

int	exec_builtin(t_env *env, char *cmd, char **args)
{
	printf("builtin cmd: %s\n", cmd);
	// if (args && *args)
	// {
	// 	while (*args)
	// 	{
	// 		printf("arg: %s\n", *args);
	// 		args++;
	// 	}
	// }
	if (!ft_strncmp(cmd, CMD_CD, ft_strlen(cmd)))
		return (cmd_cd(env, args));
	if (!ft_strncmp(cmd, CMD_ECHO, ft_strlen(cmd)))
		return (cmd_echo(args));
	if (!ft_strncmp(cmd, CMD_ENV, ft_strlen(cmd)))
		return (cmd_env(env, args));
	if (!ft_strncmp(cmd, CMD_EXIT, ft_strlen(cmd)))
		return (cmd_exit(args));
	// if (!ft_strncmp(cmd, CMD_EXPORT, ft_strlen(cmd)))
	// 	return ((args, env));
	if (!ft_strncmp(cmd, CMD_PWD, ft_strlen(cmd)))
		return (cmd_pwd());
	// if (!ft_strncmp(cmd, CMD_UNSET, ft_strlen(cmd)))
	// 	return ((args, env));
	return (FAILURE);
}

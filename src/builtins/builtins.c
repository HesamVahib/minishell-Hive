<<<<<<< HEAD:builtins/builtins.c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 17:22:37 by michoi            #+#    #+#             */
/*   Updated: 2025/05/25 01:25:15 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"

int	exec_builtin(t_env *env, char *cmd, char **args)
{
	if (!ft_strncmp(cmd, CMD_CD, ft_strlen(cmd)))
		return (cmd_cd(env, args));
	if (!ft_strncmp(cmd, CMD_ECHO, ft_strlen(cmd)))
		return (cmd_echo(args));
	if (!ft_strncmp(cmd, CMD_ENV, ft_strlen(cmd)))
		return (cmd_env(env, args));
	if (!ft_strncmp(cmd, CMD_EXIT, ft_strlen(cmd)))
		return (cmd_exit(args));
	if (!ft_strncmp(cmd, CMD_EXPORT, ft_strlen(cmd)))
		return (cmd_export(env, args));
	if (!ft_strncmp(cmd, CMD_PWD, ft_strlen(cmd)))
		return (cmd_pwd());
	if (!ft_strncmp(cmd, CMD_UNSET, ft_strlen(cmd)))
		return (cmd_unset(&env, args));
	return (FAILURE);
}
=======
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 17:22:37 by michoi            #+#    #+#             */
/*   Updated: 2025/06/09 19:40:04 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

int	exec_builtin(t_env *env, t_cmd *cmd_arg)
{
	char	*cmd;
	char	**args;

	cmd = cmd_arg->argv[0];
	args = cmd_arg->argv + 1;
	if (!ft_strncmp(cmd, CMD_CD, ft_strlen(cmd)))
		return (cmd_cd(env, args));
	if (!ft_strncmp(cmd, CMD_ECHO, ft_strlen(cmd)))
		return (cmd_echo(args));
	if (!ft_strncmp(cmd, CMD_ENV, ft_strlen(cmd)))
		return (cmd_env(env, args));
	if (!ft_strncmp(cmd, CMD_EXIT, ft_strlen(cmd)))
		return (cmd_exit(env, cmd_arg));
	if (!ft_strncmp(cmd, CMD_EXPORT, ft_strlen(cmd)))
		return (cmd_export(env, args));
	if (!ft_strncmp(cmd, CMD_PWD, ft_strlen(cmd)))
		return (cmd_pwd());
	if (!ft_strncmp(cmd, CMD_UNSET, ft_strlen(cmd)))
		return (cmd_unset(&env, args));
	return (FAILURE);
}
>>>>>>> 874a9b48f3199909f568ebc8744a2ebc01ae86ce:src/builtins/builtins.c

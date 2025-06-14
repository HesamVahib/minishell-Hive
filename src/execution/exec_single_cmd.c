/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 17:59:57 by michoi            #+#    #+#             */
/*   Updated: 2025/06/14 02:26:11 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execution.h"

static int	execute_single_cmd(const char **builtins, t_cmd *cmd, t_env *env)
{
	pid_t	child_pid;
	int		wait_stat;
	int		argv_i;

	argv_i = check_valid_argv(cmd->argv);
	if (is_in_array(builtins, cmd->argv[argv_i]))
	{
		if (open_files(cmd))
			return (FAILURE);
		if (duplicate_files(cmd))
			return (FAILURE);
		return (exec_builtin(env, cmd));
	}
	child_pid = init_child_process();
	if (child_pid == -1)
		return (FAILURE);
	if (child_pid == 0)
		execute_external_cmd(cmd, env);
	if (close_files(cmd))
		return (FAILURE);
	if (wait_for_pid(child_pid, &wait_stat))
		return (FAILURE);
	return (handle_exit_status(wait_stat));
}

int	run_single_cmd(const char **builtins, t_cmd *cmd, t_env *env)
{
	if (cmd->error)
		return (FAILURE);
	signal(SIGQUIT, SIG_DFL);
	set_and_get_exit_status(execute_single_cmd(builtins, cmd, env), true);
	return (SUCCESS);
}

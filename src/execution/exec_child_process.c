/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child_process.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 18:27:17 by michoi            #+#    #+#             */
/*   Updated: 2025/06/14 02:26:20 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execution.h"

int	run_command(t_cp *cp, char **env_arr)
{
	if (execve(cp->path, cp->args, env_arr))
	{
		free(cp->path);
		free_array(&env_arr);
		perror("execve failed");
		return (FAILURE);
	}
	return (SUCCESS);
}

/**
 * Special cases with dots as a command
 * .: filename argument required (2)
 * ..: command not found (127)
 */
void	handle_dots(t_cmd *cmd, t_env *env)
{
	int	argv_i;

	argv_i = check_valid_argv(cmd->argv);
	if (!ft_strcmp(cmd->argv[argv_i], "..") || !ft_strcmp(cmd->argv[argv_i],
			"."))
	{
		if (!ft_strcmp(cmd->argv[argv_i], ".."))
		{
			print_path_err(cmd->argv[argv_i]);
			cleanup_exit(env, cmd);
			exit(set_path_exit_code(127));
		}
		else if (!ft_strcmp(cmd->argv[argv_i], "."))
		{
			print_cmd_err(cmd->argv[argv_i], "filename argument required");
			cleanup_exit(env, cmd);
			exit(2);
		}
	}
}

static void	run_and_cleanup(t_cmd *cmd, t_env *env, t_cp *cp, char **env_arr)
{
	exit_run(env);
	cleanup_env(env);
	if (run_command(cp, env_arr))
	{
		close_files(cmd);
		free_cmd_list(cmd);
		exit(EXIT_FAILURE);
	}
}

void	execute_external_cmd(t_cmd *cmd, t_env *env)
{
	t_cp	cp;
	char	**env_arr;
	int		argv_i;

	argv_i = check_valid_argv(cmd->argv);
	ft_bzero(&cp, sizeof(t_cp));
	handle_dots(cmd, env);
	open_dup_files(cmd, env);
	env_arr = get_env_arr(env);
	if (!env_arr)
	{
		cleanup_exit(env, cmd);
		exit(EXIT_FAILURE);
	}
	cp.path = get_cmd_path(env, cmd->argv[argv_i]);
	if (!cp.path)
	{
		free_array(&env_arr);
		print_path_err(cmd->argv[argv_i]);
		cleanup_exit(env, cmd);
		exit(set_path_exit_code(errno));
	}
	cp.args = cmd->argv + (argv_i);
	run_and_cleanup(cmd, env, &cp, env_arr);
}

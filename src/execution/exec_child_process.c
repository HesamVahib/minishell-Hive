/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child_process.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 18:27:17 by michoi            #+#    #+#             */
/*   Updated: 2025/06/09 21:32:19 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execution.h"

void	run_command(t_cp *cp, char **env_arr)
{
	if (execve(cp->path, cp->args, env_arr))
	{
		free(cp->path);
		free_array(&env_arr);
		perror("execve failed");
		exit(EXIT_FAILURE);
		// close file?
	}
}

void	cleanup_process(t_cmd *cmd, t_env *env, t_cmd *head)
{
	cleanup_env(env);
	close_files(cmd);
	free_cmd_list(head);
}

int	execute_single_cmd(const char **builtins, t_cmd *cmd, t_env *env,
		t_cmd *head)
{
	pid_t	child_pid;
	int		wait_stat;
	
	if (is_in_array(builtins, cmd->argv[0]))
	{
		if (open_files(cmd))
			return (FAILURE);
		if (duplicate_files(cmd))
			return (FAILURE);
		return (exec_builtin(env, cmd, head));
	}
	else
	{
		child_pid = init_child_process();
		if (child_pid == -1)
			return (FAILURE);
		if (child_pid == 0)
			exec_external_cmd(cmd, env, head);
		if (close_files(cmd))
			return (FAILURE);
		if (wait_for_pid(child_pid, &wait_stat))
			return (FAILURE);
		return (handle_exit_status(wait_stat));
	}
	return (SUCCESS);
}

int	run_single_cmd(const char **builtins, t_cmd *cmd, t_env *env, t_cmd *head)
{
	if (cmd->error)
		return (FAILURE);
	signal(SIGQUIT, SIG_DFL);
	set_and_get_exit_status(execute_single_cmd(builtins, cmd, env, head), true);
	return (SUCCESS);
}

void	execute_cmd_in_pipe(const char **builtins, t_pipe cmd_pipe,
		t_cmd *cmd_args, t_env *env, t_cmd *head)
{
	if (redirect_pipe(*cmd_args, cmd_pipe))
		exit(EXIT_FAILURE);
	if (is_in_array(builtins, cmd_args->argv[0]))
	{
		// cleanup
		if (open_files(cmd_args))
			exit(EXIT_FAILURE);
		if (duplicate_files(cmd_args))
			exit(EXIT_FAILURE);
		exit(exec_builtin(env, cmd_args, head));
		// return (FAILURE);
	}
	exec_external_cmd(cmd_args, env, head);
}

void	exec_external_cmd(t_cmd *cmd, t_env *env, t_cmd *head)
{
	t_cp	cp;
	char	**env_arr;

	if (!ft_strcmp(cmd->argv[0], "..") || !ft_strcmp(cmd->argv[0], "."))
	{
		close_files(cmd);
		if (!ft_strcmp(cmd->argv[0], ".."))
		{
			print_path_err(cmd);
			cleanup_env(env);
			free_cmd_list(head);
			exit(set_path_exit_code(127));
		}
		else if (!ft_strcmp(cmd->argv[0], "."))
		{
			print_cmd_err(cmd->argv[0], "filename argument required");
			cleanup_env(env);
			free_cmd_list(head);
			exit(2);
		}
	}
	ft_bzero(&cp, sizeof(t_cp));
	env_arr = get_env_arr(env);
	if (!env_arr)
	{
		close_files(cmd);
		cleanup_env(env);
		free_cmd_list(head);
		exit(EXIT_FAILURE);
	}
	cp.path = get_cmd_path(env, cmd->argv[0]);
	if (!cp.path)
	{
		free_array(&env_arr);
		print_path_err(cmd);
		close_files(cmd);
		// cleanup_env(env);
		exit_run(env);
		free_cmd_list(head);
		exit(set_path_exit_code(errno));
	}
	if (open_files(cmd))
	{
		free_array(&env_arr);
		free(cp.path);
		cleanup_env(env);
		free_cmd_list(head);
		exit(EXIT_FAILURE);
	}
	if (duplicate_files(cmd))
	{
		free_array(&env_arr);
		free(cp.path);
		close_files(cmd);
		cleanup_env(env);
		free_cmd_list(head);
		// close in/outfile?
		exit(EXIT_FAILURE);
	}
	cp.args = cmd->argv;
	run_command(&cp, env_arr);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child_process.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 18:27:17 by michoi            #+#    #+#             */
/*   Updated: 2025/05/27 16:11:19 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execution.h"

void	print_path_err(t_cmd *cmd)
{
	if (errno == EACCES || errno == ENOENT || errno == EISDIR)
		print_cmd_err(cmd->argv[0], strerror(errno));
	else
		print_basic_error(cmd->argv[0], "command not found");
}

int	set_path_exit_code(int err_no)
{
	int	code;

	if (err_no == EACCES || err_no == EISDIR)
		code = 126;
	else
		code = 127;
	return (code);
}

void	exec_external_cmd(t_cmd *cmd, t_env *env)
{
	t_cp	cp;
	char	**env_arr;

	// printf("infile %d, outfile: %d\n", cmd->infile_fd, cmd->outfile_fd);
	ft_bzero(&cp, sizeof(t_cp));
	env_arr = get_env_arr(env);
	// close file?
	if (!env_arr)
		exit(EXIT_FAILURE);
	cp.path = get_cmd_path(env, cmd->argv[0]);
	if (!cp.path)
	{
		free_array(&env_arr);
		print_path_err(cmd);
		close_files(cmd);
		exit(set_path_exit_code(errno));
		// close file
	}
	if (open_infile(cmd))
		exit(EXIT_FAILURE);
	// printf("close files in child\n");
	if (duplicate_files(cmd))
	{
		free_array(&env_arr);
		free(cp.path);
		// close in/outfile?
		exit(EXIT_FAILURE);
	}
	cp.args = cmd->argv;
	run_command(&cp, env_arr);
}

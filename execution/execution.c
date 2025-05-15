/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvahib <hvahib@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 22:01:29 by michoi            #+#    #+#             */
/*   Updated: 2025/05/15 14:12:58 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execution.h"

void	print_arr(char **arr)
{
	while (*arr)
	{
		printf("%s\n", *arr);
		arr++;
	}
}

pid_t	init_child_process(void)
{
	pid_t	cp;

	cp = fork();
	if (cp == -1)
	{
		perror("Fork failed");
		return (errno);
	}
	return (cp);
}

// int	exec_single_cmd(t_cmd *cmd_args, t_env *env, bool piped)



int	exec_cmd(t_cmd *cmd_args, t_env *env)
{
	t_cp		cp;
	pid_t		child_pid;
	int			wait_stat;
	bool		is_piped_already;
	int			pipe_fd[2];
	const char	*builtins[] = {CMD_CD, CMD_ECHO, CMD_ENV, CMD_EXPORT, CMD_PWD,
			CMD_UNSET, NULL};
	char		**env_arr;

	printf("fd: %d\n", cmd_args->outfile_fd);
	// if there's only one cmd (no pipe)
	if (!cmd_args->next)
	{
		// builtin
		if (is_in_array(builtins, cmd_args->argv[0]))
		{
			// call_builtin
			if (exec_builtin(env, cmd_args->argv[0], cmd_args->argv + 1))
				return (FAILURE);
		}
		else
			{
				// fork
				child_pid = init_child_process();
				if (child_pid == 0)
				{
					env_arr = get_env_arr(env);
					// close file?
					if (!env_arr)
						exit(EXIT_FAILURE);
					cp.path = get_cmd_path(env, cmd_args->argv[0]);
					if (!cp.path)
					{
						if (errno == EACCES || errno == ENOENT
							|| errno == EISDIR)
							print_cmd_err(cmd_args->argv[0], strerror(errno));
						else
							print_basic_error(cmd_args->argv[0],
								"command not found");
						free_array(&env_arr);
						exit(EXIT_FAILURE);
						// close file
					}
					cp.args = cmd_args->argv;
					// execve
					if (execve(cp.path, cp.args, env_arr))
					{
						free(cp.path);
						free_array(&env_arr);
						perror("execve failed");
						exit(EXIT_FAILURE);
						// close file
					}
				}
				if (waitpid(child_pid, &wait_stat, 0) == -1)
					return (FAILURE);
			}
		return (SUCCESS);
	}



	is_piped_already = false;
	while (cmd_args)
	{
		// print_arr(cmd_args->argv);
		// if there's only one cmd (no pipe)
		if (!is_piped_already && !cmd_args->is_piped)
		{
			// builtin
			if (is_in_array(builtins, cmd_args->argv[0]))
			{
				// call_builtin
				if (exec_builtin(env, cmd_args->argv[0], cmd_args->argv + 1))
					return (FAILURE);
			}
			else
			{
				// fork
				child_pid = init_child_process();
				if (child_pid == 0)
				{
					env_arr = get_env_arr(env);
					// close file?
					if (!env_arr)
						exit(EXIT_FAILURE);
					cp.path = get_cmd_path(env, cmd_args->argv[0]);
					if (!cp.path)
					{
						if (errno == EACCES || errno == ENOENT
							|| errno == EISDIR)
							print_cmd_err(cmd_args->argv[0], strerror(errno));
						else
							print_basic_error(cmd_args->argv[0],
								"command not found");
						free_array(&env_arr);
						exit(EXIT_FAILURE);
						// close file
					}
					cp.args = cmd_args->argv;
					// execve
					if (execve(cp.path, cp.args, env_arr))
					{
						free(cp.path);
						free_array(&env_arr);
						perror("execve failed");
						exit(EXIT_FAILURE);
						// close file
					}
				}
				if (waitpid(child_pid, &wait_stat, 0) == -1)
					return (FAILURE);
			}
		}
		else
		{
			is_piped_already = true;

			if (!pipe(pipe_fd))
				return (FAILURE);

			// int i = 0;



		}
		cmd_args = cmd_args->next;
	}
	return (SUCCESS);
}

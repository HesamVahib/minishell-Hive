/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 22:01:29 by michoi            #+#    #+#             */
/*   Updated: 2025/05/11 20:34:59 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execution.h"

int	exec_cmd(t_cmd *cmd_args, t_env *env)
{
	t_cp		cp;
	pid_t		child_pid;
	int			wait_stat;
	bool		is_piped_already;
	const char	*builtins[] = {CMD_CD, CMD_ECHO, CMD_ENV, CMD_EXPORT, CMD_PWD,
			CMD_UNSET, NULL};
	char		**env_arr;

	is_piped_already = false;
	// open_create_files
	// while (cmd_args->argv)
	// {
	// 	printf("%s\n", *(cmd_args->argv));
	// 	(cmd_args->argv)++;
	// }
	while (cmd_args)
	{
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
				child_pid = fork();
				if (child_pid == -1)
				{
					perror("Fork failed");
					return (FAILURE);
				}
				if (child_pid == 0)
				{
					printf("cmd is : %s", cmd_args->argv[0]);
					env_arr = get_env_arr(env);
					// close file?
					if (!env_arr)
						exit(EXIT_FAILURE);
					cp.path = get_cmd_path(env, cmd_args->argv[0]);
					cp.args = cmd_args->argv;
					if (!cp.path)
					{
						printf("no path for execve\n");
						free_array(&env_arr);
						exit(EXIT_FAILURE);
						// close file
					}
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
			//	is_piped_already = true;
		}
		cmd_args = cmd_args->next;
	}
	return (SUCCESS);
}
